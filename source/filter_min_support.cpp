#include "common.hpp"
#include "filter_min_support.hpp"

using namespace std;

// throw away fusions with few supporting reads
unsigned int filter_min_support(fusions_t& fusions, const unsigned int min_support) {
	unsigned int remaining = 0;
	for (fusions_t::iterator i = fusions.begin(); i != fusions.end(); ++i) {

		if (i->second.filter != NULL)
			continue; // fusion has already been filtered

		if (i->second.split_reads1 + i->second.split_reads2 + i->second.discordant_mates < min_support ||
		    i->second.breakpoint_overlaps_both_genes() && i->second.split_reads1 + i->second.split_reads2 < min_support)
			i->second.filter = FILTERS.at("min_support");
		else
			remaining++;
	}
	return remaining;
}
