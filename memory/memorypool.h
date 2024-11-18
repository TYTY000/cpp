/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorypool.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:40:38 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/02 16:31:28 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MEMORY_POOL__
#define __MEMORY_POOL__

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

template <typename T, size_t BlockSize = 4096> class MemoryPool {
public:
  using value_type = T;
  using ref = T &;
  using ptr = T *;
  using const_ref = const T &;
  using const_ptr = const T *;
  using size_type = size_t;
  using diff_type = ptrdiff_t;
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;

  template <typename U> struct rebind {
    using other = MemoryPool<U>;
  };

  MemoryPool() noexcept;
  MemoryPool(const MemoryPool &) noexcept;
  MemoryPool(MemoryPool &&) noexcept;
  template <class U> MemoryPool(const MemoryPool<U> &) noexcept;
  ~MemoryPool() noexcept;

  MemoryPool &operator=(const MemoryPool &) = delete;
  MemoryPool &operator=(MemoryPool &&) noexcept;

  ptr address(ref) const noexcept;
  const_ptr address(const_ref) const noexcept;

  // Can only allocate one object at a time. n and hint are ignored
  ptr allocate(size_type n = 1, const_ptr hint = 0);
  void deallocate(ptr p, size_type n = 1);

  size_type max_size() const noexcept;

  template <class U, class... Args> void construct(U *, Args &&...);
  template <class U> void destroy(U *);

  template <class... Args> ptr newElement(Args &&...);
  void deleteElement(ptr);

private:
  // 在这个内存池的实现中，block 是内存的物理单位，每个 block 包含多个
  // slot。每个 slot 都可以存储一个 T 类型的对象。block 的大小是固定的（由
  // BlockSize 指定），而 slot 的大小则取决于 T 的大小。这样，我们可以在一个
  // block 中存储多个 T 对象，每个对象占用一个 slot。
  // 这种设计可以提高内存的利用率，因为我们可以在一个 block
  // 中存储多个对象，而不是为每个对象单独分配一个 block。这也是为什么我们需要
  // slot_ptr_ 和 data_ptr_ 两种不同类型的指针：slot_ptr_ 用来指向 slot，而
  // data_ptr_ 用来指向 block。这样，我们可以通过 slot_ptr_ 来访问和操作
  // slot，通过 data_ptr_ 来访问和操作 block。
  union Slot_ {
    value_type element;
    Slot_ *next;
  };
  using data_ptr_ = char *;
  using slot_type_ = Slot_;
  using slot_ptr_ = Slot_ *;

  slot_ptr_ currentBlock_;
  slot_ptr_ currentSlot_;
  slot_ptr_ lastSlot_;
  slot_ptr_ freeSlots_;

  size_type padPointer(data_ptr_, size_type) const noexcept;
  void allocateBlock();

  static_assert(BlockSize >= 2 * sizeof(slot_type_), "BlockSize too small.");
};

#include "memorypool.cc"
#endif // __MEMORY_POOL__
