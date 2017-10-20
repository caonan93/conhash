#ifndef __CONHASH__
#define __CONHASH__
#include <map>

#include "def.h"
#include "CNonCopy.h"
#include "md5.h"
#include <vector>

using namespace std;

namespace conhash
{
	typedef uint64_t (*PHASH_FUN)(const string& key) ;

	class CConhash:public Noncopyable
	{
	public:
		CConhash(PHASH_FUN pfun = NULL) :_virtual_num(0), _phash_fun(NULL)
		{
			if (pfun == NULL)
			{
				_phash_fun = def_hash_fun;
			}
			else
			{
				_phash_fun = pfun;
			}
		}

		bool add_node(HashNode& node);
		bool del_node(HashNode& node);
		HashNode conhash(const string& hashkey);

		inline uint32_t virtual_node_num()
		{
			return _virtual_num;
		}

		void show_virtual_nodes()
		{
			for (map<string, HashNode>::iterator it= _virtual_nodes.begin();it != _virtual_nodes.end();++it)
			{
				HashNode& node = it->second;
				printf("node name %s,virtualkey %s\n", node.node_name.c_str(), it->first.c_str());
			}
		}
	private:
		static uint64_t def_hash_fun(const string& key);
		static void conhash_md5_digest(const char *instr, char digest[16])
		{
			md5_state_t md5state;

			md5_init(&md5state);
			md5_append(&md5state, reinterpret_cast<const md5_byte_t *>(instr), strlen(instr));
			md5_finish(&md5state, reinterpret_cast<md5_byte_t *>(digest));
		}

	private:
		map<string, HashNode> _virtual_nodes;
		map<string,HashNode> _real_nodes;
		uint32_t _virtual_num;
		PHASH_FUN _phash_fun;
	};
}
#endif
