#include "BACH/sstable/SSTableBuilder.h"

namespace BACH
{
	SSTableBuilder::SSTableBuilder(std::shared_ptr<FileWriter> _fileWriter) :
		writer(_fileWriter)
	{}
	void SSTableBuilder::AddFilter(idx_t keys_num, double false_positive)
	{
		filter.push_back(std::make_shared<BloomFilter>(keys_num, false_positive));
	}
	void SSTableBuilder::SetSrcRange(vertex_t src_b, vertex_t src_e)
	{
		this->src_b = src_b;
        this->src_e = src_e;
	}
	void SSTableBuilder::FinishSrc()
	{
		src_index.push_back(src_cnt);
		min_t.push_back(now_min_t);
		max_t.push_back(now_max_t);
		now_min_t = TOMBSTONE;
		now_max_t = 0;
	}
	void SSTableBuilder::AddEdge(vertex_t src, vertex_t dst, edge_property_t edge_property)
	{
        std::string temp_data;
		util::PutFixed(temp_data, dst);
        util::PutFixed(temp_data, edge_property);
        writer->append(temp_data.data(), temp_data.size());
		this->filter[src]->insert_pair(src, dst);
		this->src_edge_num ++;
	}
	void SSTableBuilder::ArrangeCurrentSrcInfo()
	{
		edge_allocation_list.push_back(this->src_edge_num);
        this->src_edge_num = 0;
	}
	void SSTableBuilder::ArrangeSSTableInfo()
	{   
        edge_num_t edge_num_prefix_sum = 0;
        for (auto num : this->edge_allocation_list) 
        {
            edge_num_prefix_sum += num;
            writer->append(&edge_num_prefix_sum, edge_num_t);
        }
		for (auto& i : this->filter)
		{
			writer->append(i->data().data(), i->data().size());
		}
		size_t filter_len_prefix_sum = 0;
		std::string metadata;
		for (auto& i : this->filter)
		{
			filter_len_prefix_sum += i->data().size();
			util::PutFixed(metadata, filter_len_prefix_sum);
			util::PutFixed(metadata, (idx_t)i->get_func_num());
		}
		util::PutFixed(metadata, src_b);
		util::PutFixed(metadata, src_e);
		util::PutFixed(metadata, edge_num_prefix_sum);
		writer->append(metadata.data(), metadata.size());
		writer->flush();
	}
}
// query 文件写入是大批量一次性写入更快吗？这样需要额外将vector转成长字符串的花销