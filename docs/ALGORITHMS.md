# 🧠 Memory Allocation Algorithms in Operating Systems

## A. Contiguous Memory Allocation Algorithms
These algorithms allocate a single continuous block of memory to a process.

### 1. First Fit
- Allocates the first available block that's large enough.
- ✅ Fast
- ❌ Causes fragmentation at the start of memory.

### 2. Best Fit
- Allocates the smallest block that fits the request.
- ✅ Reduces wasted space
- ❌ Leaves many small unusable holes (external fragmentation).

### 3. Worst Fit
- Allocates the largest available block.
- ✅ Leaves big leftover space
- ❌ Often leads to high fragmentation.

### 4. Next Fit
- Like First Fit but continues search from the last allocated block.
- ✅ Can be faster than First Fit
- ❌ Still leads to fragmentation.

---

## B. Non-Contiguous Memory Allocation Techniques
These allow process memory to be split across non-adjacent blocks.

### 1. Paging
- Memory is divided into fixed-size pages and frames.
- ✅ No external fragmentation
- ❌ Overhead from page tables.

### 2. Segmentation
- Memory is divided based on logical segments (code, data, stack).
- ✅ Logical organization
- ❌ Suffers from external fragmentation.

### 3. Segmented Paging (or Paged Segmentation)
- Hybrid: segments are divided into pages.
- ✅ Benefits of both segmentation and paging
- ❌ Increased complexity.

---

## C. Buddy System Allocation
A compromise between performance and memory utilization.

### 1. Buddy System
- Memory is allocated in powers of two.
- Blocks can be split and merged with their "buddies".
- ✅ Fast allocation and deallocation
- ❌ Internal fragmentation from size rounding.

---

## D. Slab Allocation (Kernel Level)
Used for efficiently allocating memory for objects of the same size.

### 1. Slab Allocator
- Preallocates slabs for frequent object types.
- ✅ Minimizes fragmentation
- ✅ Fast object allocation
- ❌ Less efficient for variable-size objects.

---

## E. Heap-Based Dynamic Allocation (User-Level Libraries)
These are used by applications via functions like `malloc` and `free`.

### 1. malloc Implementations (ptmalloc, jemalloc, tcmalloc)
- Use a mix of:
  - First Fit / Best Fit
  - Segregated free lists
  - Bins by size classes
  - Chunk splitting and merging
- ✅ Highly optimized
- ❌ Complex internal logic

---

## F. Virtual Memory Techniques
Used by OS to extend physical memory with disk-based storage.

### 1. Demand Paging
- Pages are loaded into RAM only when accessed.
- ✅ Efficient memory use
- ❌ Page faults can slow performance.

### 2. Swapping
- Whole processes or memory regions are moved to disk.
- ✅ Increases usable memory
- ❌ Very slow, affects performance.

---

## 📊 Quick Comparison Table

| Algorithm          | Fragmentation   | Speed            | Use Case                      |
|--------------------|-----------------|------------------|-------------------------------|
| First Fit          | External        | Fast             | Simple general allocation     |
| Best Fit           | External        | Slow             | Space optimization            |
| Worst Fit          | External        | Poor             | Rarely used                   |
| Next Fit           | External        | Medium           | Performance trade-off         |
| Paging             | None (External) | Fast             | Modern OS memory management   |
| Segmentation       | External        | Medium           | Logical memory division       |
| Buddy System       | Internal        | Fast             | OS-level allocation           |
| Slab Allocator     | Minimal         | Very Fast        | Kernel object allocation      |
| malloc variants    | Mixed           | Very Fast        | User-space dynamic memory     |
| Demand Paging      | None            | Slow (if faults) | Virtual memory                |
| Swapping           | None            | Very Slow        | Memory overcommitment         |