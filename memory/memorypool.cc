/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorypool.cc                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: TYTY000 <767280080@qq.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:54:57 by TYTY000           #+#    #+#             */
/*   Updated: 2024/05/02 16:13:28 by TYTY000          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "memorypool.h"
template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool() noexcept {
  currentBlock_ = nullptr;
  currentSlot_ = nullptr;
  lastSlot_ = nullptr;
  freeSlots_ = nullptr;
}

template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool(const MemoryPool &mp) noexcept
    : MemoryPool() {}

template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::MemoryPool(MemoryPool &&mp) noexcept {
  currentBlock_ = mp.currentBlock_;
  mp.currentBlock_ = nullptr;
  currentSlot_ = mp.currentSlot_;
  lastSlot_ = mp.lastSlot_;
  freeSlots_ = mp.freeSlots_;
}

template <typename T, size_t BlockSize>
template <class U>
MemoryPool<T, BlockSize>::MemoryPool(const MemoryPool<U> &) noexcept
    : MemoryPool() {}

template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize> &
MemoryPool<T, BlockSize>::operator=(MemoryPool &&mp) noexcept {
  if (this != &mp) {
    std::swap(currentBlock_, mp.currentBlock_);
    currentSlot_ = mp.currentSlot_;
    lastSlot_ = mp.lastSlot_;
    freeSlots_ = mp.freeSlots_;
  }
  return *this;
}

template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize>::~MemoryPool() noexcept {
  slot_ptr_ cur = currentBlock_;
  while (cur) {
    slot_ptr_ next = cur->next;
    operator delete(reinterpret_cast<void *>(cur));
    // here, operator delete means global scope delete, which acts like free in
    // C. secondly, delete(reinterpret_cast<void*>(T* p)) won't trigger
    // destructor of T, only to free content of p.
    cur = next;
  }
}

template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::ptr
MemoryPool<T, BlockSize>::address(ref x) const noexcept {
  return &x;
}

template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::const_ptr
MemoryPool<T, BlockSize>::address(const_ref x) const noexcept {
  return &x;
}

template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::ptr
MemoryPool<T, BlockSize>::allocate(size_type n, const_ptr hint) {
  if (freeSlots_ != nullptr) {
    ptr p = reinterpret_cast<ptr>(freeSlots_);
    freeSlots_ = freeSlots_->next;
    return p;
  } else {
    if (currentSlot_ >= lastSlot_) {
      allocateBlock();
    }
    return reinterpret_cast<ptr>(currentSlot_++);
  }
}

template <typename T, size_t BlockSize>
inline void MemoryPool<T, BlockSize>::deallocate(ptr p, size_type n) {
  if (p != nullptr) {
    reinterpret_cast<slot_ptr_>(p)->next = freeSlots_;
    freeSlots_ = reinterpret_cast<slot_ptr_>(p);
  }
}

template <typename T, size_t BlockSize>
inline typename MemoryPool<T, BlockSize>::size_type
MemoryPool<T, BlockSize>::max_size() const noexcept {
  size_type maxBlocks = -1 / BlockSize;
  return maxBlocks * (BlockSize - sizeof(data_ptr_)) / sizeof(slot_type_);
}

template <typename T, size_t BlockSize>
template <class U, class... Args>
inline void MemoryPool<T, BlockSize>::construct(U *p, Args &&...args) {
  new (p) U(std::forward<Args>(args)...);
}

template <typename T, size_t BlockSize>
template <class U>
inline void MemoryPool<T, BlockSize>::destroy(U *p) {
  p->~U();
}

template <typename T, size_t BlockSize>
template <class... Args>
inline typename MemoryPool<T, BlockSize>::ptr
MemoryPool<T, BlockSize>::newElement(Args &&...args) {
  ptr p = allocate();
  construct<value_type>(p, std::forward<Args>(args)...);
  return p;
}

template <typename T, size_t BlockSize>
inline void MemoryPool<T, BlockSize>::deleteElement(ptr p) {
  if (p != nullptr) {
    p->~value_type();
    deallocate(p);
  }
}

template <typename T, size_t BlockSize>
typename MemoryPool<T, BlockSize>::size_type
MemoryPool<T, BlockSize>::padPointer(data_ptr_ p,
                                     size_type align) const noexcept {
  uintptr_t ptr = reinterpret_cast<uintptr_t>(p);
  return ((align - ptr) % align);
}

template <typename T, size_t BlockSize>
inline void MemoryPool<T, BlockSize>::allocateBlock() {
  data_ptr_ p = reinterpret_cast<data_ptr_>(operator new(BlockSize));
  reinterpret_cast<slot_ptr_>(p)->next = currentBlock_;
  currentBlock_ = reinterpret_cast<slot_ptr_>(p);
  data_ptr_ block = p + sizeof(slot_ptr_);
  size_type padding = padPointer(block, alignof(slot_type_));
  currentSlot_ = reinterpret_cast<slot_ptr_>(padding + block);
  lastSlot_ =
      reinterpret_cast<slot_ptr_>(p + BlockSize - sizeof(slot_type_) + 1);
}
