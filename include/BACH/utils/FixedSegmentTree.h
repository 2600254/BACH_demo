#pragma once 

#include <atomic>
#include <vector>
#include "ConcurrentArray.h"

namespace BACH
{
	class FixedSegmentTree
	{
	public:
		FixedSegmentTree(std::shared_ptr<Options> options) :
			tree(5),
			memory_num(options->MEMORY_MERGE_NUM),
			merge_num(options->FILE_MERGE_NUM) {}
		void push_back()
		{
			auto src = size.fetch_add(1);
			if (src % memory_num == 0)
			{
				tree[0].push_back(src);
				src /= memory_num;
				for (size_t i = 1; i < tree.size(); i++)
				{
					if (src % merge_num == 0)
					{
						tree[i].push_back(src);
						src /= merge_num;
					}
					else
					{
						break;
					}
				}
			}
		}
		void add_at(size_t index, size_t value)
		{
			index /= memory_num;
			tree[0][index] += value;
			for (size_t i = 1; i < tree.size(); i++)
			{
				index /= merge_num;
				tree[i][index] += value;
			}
		}
		size_t range_query(vertex_t index, idx_t level) const
		{
			index /= memory_num;
			for (idx_t i = 1; i <= level; ++i)
				index /= merge_num;
			return tree[level][index];
		}
	private:
		std::vector<ConcurrentArray<size_t>> tree;
		vertex_t memory_num, merge_num;
		std::atomic<size_t> size = 0;
	};
}