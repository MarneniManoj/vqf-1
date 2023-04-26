/*
 * ============================================================================
 *
 *       Filename:  vqf_filter.h
 *
 *         Author:  Prashant Pandey (), ppandey@berkeley.edu
 *   Organization: 	LBNL/UCB 
 *
 * ============================================================================
 */

#ifndef _VQF_FILTER_H_
#define _VQF_FILTER_H_
#include <vector>
#include <inttypes.h>
#include <stdbool.h>

#ifdef __cplusplus
#define restrict __restrict__
extern "C" {
#endif

   // NOTE: Currently the code only works for TAG_BITS 8
   // This filter variant is being tuned exclusively for MetaHipMer, so only the minimum required for that application is being done.
#define TAG_BITS 8

	// metadata: 1 --> end of the run
	// Each 1 is preceded by k 0s, where k is the number of remainders in that
	// run.


#if TAG_BITS == 8
	// We are using 8-bit tags.
	// One block consists of 28 8-bit slots covering 36 buckets, and 28+36 = 64
	// bits of metadata. Each tag has an 8-bit value for 8+28+28 = 64
	typedef struct __attribute__ ((__packed__)) vqf_block {
		uint64_t md;
		uint16_t tags[28];
	} vqf_block;
#endif

	typedef struct vqf_metadata {
		uint64_t total_size_in_bytes;
		uint64_t key_remainder_bits;
		uint64_t range;
		uint64_t nblocks;
		uint64_t nelts;
		uint64_t nslots;
	} vqf_metadata;

	typedef struct vqf_filter {
		vqf_metadata metadata;
		vqf_block blocks[];
	} vqf_filter;

	vqf_filter * vqf_init(uint64_t nslots);

	bool vqf_insert(vqf_filter * restrict filter, uint64_t hash);

	bool vqf_insert_val(vqf_filter * restrict filter, uint64_t hash, uint8_t val);
	
	bool vqf_remove(vqf_filter * restrict filter, uint64_t hash);

	bool vqf_is_present(vqf_filter * restrict filter, uint64_t hash);
    bool vqf_query(vqf_filter * restrict filter, uint64_t hash, uint8_t & value);
    bool vqf_query_iter(vqf_filter * restrict filter, uint64_t hash, std::vector<uint8_t>& values);

#ifdef __cplusplus

}
#endif

#endif	// _VQF_FILTER_H_


