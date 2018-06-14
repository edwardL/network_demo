#ifndef _ALLOC_H
#define _ALLOC_H

#include <cstdlib>

namespace TinySTL {
	/*
	空间配置器
	*/
	class alloc {
	private:
		enum {ALIGN = 8}; // 小型区块的上调边界 EAlign
		enum  {MAXBYTES = 128}; //小型区块的上限，超过的区块由malloc 分配 EMaxBytes
		enum  { NFREELISTS = MAXBYTES / ALIGN}; // free-list 的个数 ENFreeLists
		enum  {NOBJS = 20}; //每次增加的节点数 ENObjs
		 
	private:
		// free-list 的节点构造
		union obj {
			union obj* next;
			char client[1];
		};
		static obj *free_list[alloc::NFREELISTS];

	private:
		static char *start_free; // 内存池起始位置
		static char *end_free;	// 内存池结束位置
		static size_t heap_size;

	private:
		// 将bytes 上调至8 的倍数
		static size_t ROUND_UP(size_t bytes) {
			return ((bytes + alloc::ALIGN - 1) & ~(alloc::ALIGN -1));
		}

		// 根据区块大小， 决定使用第n号free-list, n 从0 开始算起
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes) + alloc::ALIGN -1) / alloc::ALIGN - 1);
		}

		// 返回一个大小为n 的对象， 并可能加入大小为n 的其他区块到free-list 
		static void *refill(size_t n);
		// 配置一大块空间, 可以容易nobjs 个大小为size 的区块
		static char * chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void *allocate(size_t bytes);
		static void deallocate(void* ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_sz , size_t new_sz);
	};
}


#endif