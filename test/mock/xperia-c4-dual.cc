#include <gtest/gtest.h>

#include <cpuinfo.h>
#include <cpuinfo-mock.h>


TEST(PROCESSORS, count) {
	ASSERT_EQ(8, cpuinfo_get_processors_count());
}

TEST(PROCESSORS, non_null) {
	ASSERT_TRUE(cpuinfo_get_processors());
}

TEST(PROCESSORS, smt_id) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_processor(i)->smt_id);
	}
}

TEST(PROCESSORS, core) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_EQ(cpuinfo_get_core(i), cpuinfo_get_processor(i)->core);
	}
}

TEST(PROCESSORS, cluster) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		switch (i) {
			case 0:
			case 1:
			case 2:
			case 3:
				ASSERT_EQ(cpuinfo_get_cluster(0), cpuinfo_get_processor(i)->cluster);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				ASSERT_EQ(cpuinfo_get_cluster(1), cpuinfo_get_processor(i)->cluster);
				break;
		}
	}
}

TEST(PROCESSORS, package) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_EQ(cpuinfo_get_package(0), cpuinfo_get_processor(i)->package);
	}
}

TEST(PROCESSORS, DISABLED_linux_id) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		switch (i) {
			case 0:
			case 1:
			case 2:
			case 3:
				ASSERT_EQ(i + 4, cpuinfo_get_processor(i)->linux_id);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				ASSERT_EQ(i - 4, cpuinfo_get_processor(i)->linux_id);
				break;
		}
	}
}

TEST(PROCESSORS, l1i) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_EQ(cpuinfo_get_l1i_cache(i), cpuinfo_get_processor(i)->cache.l1i);
	}
}

TEST(PROCESSORS, l1d) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_EQ(cpuinfo_get_l1d_cache(i), cpuinfo_get_processor(i)->cache.l1d);
	}
}

TEST(PROCESSORS, l2) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		switch (i) {
			case 0:
			case 1:
			case 2:
			case 3:
				ASSERT_EQ(cpuinfo_get_l2_cache(0), cpuinfo_get_processor(i)->cache.l2);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				ASSERT_EQ(cpuinfo_get_l2_cache(1), cpuinfo_get_processor(i)->cache.l2);
				break;
		}
	}
}

TEST(PROCESSORS, l3) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_FALSE(cpuinfo_get_processor(i)->cache.l3);
	}
}

TEST(PROCESSORS, l4) {
	for (uint32_t i = 0; i < cpuinfo_get_processors_count(); i++) {
		ASSERT_FALSE(cpuinfo_get_processor(i)->cache.l4);
	}
}

TEST(CORES, count) {
	ASSERT_EQ(8, cpuinfo_get_cores_count());
}

TEST(CORES, non_null) {
	ASSERT_TRUE(cpuinfo_get_cores());
}

TEST(CORES, processor_start) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(i, cpuinfo_get_core(i)->processor_start);
	}
}

TEST(CORES, processor_count) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(1, cpuinfo_get_core(i)->processor_count);
	}
}

TEST(CORES, core_id) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(i, cpuinfo_get_core(i)->core_id);
	}
}

TEST(CORES, cluster) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		switch (i) {
			case 0:
			case 1:
			case 2:
			case 3:
				ASSERT_EQ(cpuinfo_get_cluster(0), cpuinfo_get_core(i)->cluster);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				ASSERT_EQ(cpuinfo_get_cluster(1), cpuinfo_get_core(i)->cluster);
				break;
		}
	}
}

TEST(CORES, package) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(cpuinfo_get_package(0), cpuinfo_get_core(i)->package);
	}
}

TEST(CORES, vendor) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(cpuinfo_vendor_arm, cpuinfo_get_core(i)->vendor);
	}
}

TEST(CORES, uarch) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(cpuinfo_uarch_cortex_a53, cpuinfo_get_core(i)->uarch);
	}
}

TEST(CORES, midr) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(UINT32_C(0x410FD032), cpuinfo_get_core(i)->midr);
	}
}

TEST(CORES, DISABLED_frequency) {
	for (uint32_t i = 0; i < cpuinfo_get_cores_count(); i++) {
		ASSERT_EQ(UINT64_C(1690000000), cpuinfo_get_core(i)->frequency);
	}
}

TEST(PACKAGES, count) {
	ASSERT_EQ(1, cpuinfo_get_packages_count());
}

TEST(PACKAGES, name) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ("MediaTek MT6752",
			std::string(cpuinfo_get_package(i)->name,
				strnlen(cpuinfo_get_package(i)->name, CPUINFO_PACKAGE_NAME_MAX)));
	}
}

TEST(PACKAGES, gpu_name) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ("ARM Mali-T760",
			std::string(cpuinfo_get_package(i)->gpu_name,
				strnlen(cpuinfo_get_package(i)->gpu_name, CPUINFO_GPU_NAME_MAX)));
	}
}

TEST(PACKAGES, processor_start) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_package(i)->processor_start);
	}
}

TEST(PACKAGES, processor_count) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ(8, cpuinfo_get_package(i)->processor_count);
	}
}

TEST(PACKAGES, core_start) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_package(i)->core_start);
	}
}

TEST(PACKAGES, core_count) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ(8, cpuinfo_get_package(i)->core_count);
	}
}

TEST(PACKAGES, cluster_start) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_package(i)->cluster_start);
	}
}

TEST(PACKAGES, cluster_count) {
	for (uint32_t i = 0; i < cpuinfo_get_packages_count(); i++) {
		ASSERT_EQ(2, cpuinfo_get_package(i)->cluster_count);
	}
}

TEST(ISA, thumb) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_thumb());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_thumb());
	#endif
}

TEST(ISA, thumb2) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_thumb2());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_thumb2());
	#endif
}

TEST(ISA, armv5e) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v5e());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v5e());
	#endif
}

TEST(ISA, armv6) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v6());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v6());
	#endif
}

TEST(ISA, armv6k) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v6k());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v6k());
	#endif
}

TEST(ISA, armv7) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v7());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v7());
	#endif
}

TEST(ISA, armv7mp) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v7mp());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v7mp());
	#endif
}

TEST(ISA, idiv) {
	ASSERT_TRUE(cpuinfo_has_arm_idiv());
}

TEST(ISA, vfpv2) {
	ASSERT_FALSE(cpuinfo_has_arm_vfpv2());
}

TEST(ISA, vfpv3) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3());
}

TEST(ISA, vfpv3_d32) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3_d32());
}

TEST(ISA, vfpv3_fp16) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3_fp16());
}

TEST(ISA, vfpv3_fp16_d32) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3_fp16_d32());
}

TEST(ISA, vfpv4) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv4());
}

TEST(ISA, vfpv4_d32) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv4_d32());
}

TEST(ISA, wmmx) {
	ASSERT_FALSE(cpuinfo_has_arm_wmmx());
}

TEST(ISA, wmmx2) {
	ASSERT_FALSE(cpuinfo_has_arm_wmmx2());
}

TEST(ISA, neon) {
	ASSERT_TRUE(cpuinfo_has_arm_neon());
}

TEST(ISA, neon_fp16) {
	ASSERT_TRUE(cpuinfo_has_arm_neon_fp16());
}

TEST(ISA, neon_fma) {
	ASSERT_TRUE(cpuinfo_has_arm_neon_fma());
}

TEST(ISA, atomics) {
	ASSERT_FALSE(cpuinfo_has_arm_atomics());
}

TEST(ISA, neon_rdm) {
	ASSERT_FALSE(cpuinfo_has_arm_neon_rdm());
}

TEST(ISA, fp16_arith) {
	ASSERT_FALSE(cpuinfo_has_arm_fp16_arith());
}

TEST(ISA, jscvt) {
	ASSERT_FALSE(cpuinfo_has_arm_jscvt());
}

TEST(ISA, fcma) {
	ASSERT_FALSE(cpuinfo_has_arm_fcma());
}

TEST(ISA, aes) {
	#if CPUINFO_ARCH_ARM64
		ASSERT_TRUE(cpuinfo_has_arm_aes());
	#elif CPUINFO_ARCH_ARM
		ASSERT_FALSE(cpuinfo_has_arm_aes());
	#endif
}

TEST(ISA, sha1) {
	#if CPUINFO_ARCH_ARM64
		ASSERT_TRUE(cpuinfo_has_arm_sha1());
	#elif CPUINFO_ARCH_ARM
		ASSERT_FALSE(cpuinfo_has_arm_sha1());
	#endif
}

TEST(ISA, sha2) {
	#if CPUINFO_ARCH_ARM64
		ASSERT_TRUE(cpuinfo_has_arm_sha2());
	#elif CPUINFO_ARCH_ARM
		ASSERT_FALSE(cpuinfo_has_arm_sha2());
	#endif
}

TEST(ISA, pmull) {
	#if CPUINFO_ARCH_ARM64
		ASSERT_TRUE(cpuinfo_has_arm_pmull());
	#elif CPUINFO_ARCH_ARM
		ASSERT_FALSE(cpuinfo_has_arm_pmull());
	#endif
}

TEST(ISA, crc32) {
	#if CPUINFO_ARCH_ARM64
		ASSERT_TRUE(cpuinfo_has_arm_crc32());
	#elif CPUINFO_ARCH_ARM
		ASSERT_FALSE(cpuinfo_has_arm_crc32());
	#endif
}

TEST(L1I, count) {
	ASSERT_EQ(8, cpuinfo_get_l1i_caches_count());
}

TEST(L1I, non_null) {
	ASSERT_TRUE(cpuinfo_get_l1i_caches());
}

TEST(L1I, size) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(16 * 1024, cpuinfo_get_l1i_cache(i)->size);
	}
}

TEST(L1I, associativity) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(2, cpuinfo_get_l1i_cache(i)->associativity);
	}
}

TEST(L1I, sets) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(cpuinfo_get_l1i_cache(i)->size,
			cpuinfo_get_l1i_cache(i)->sets * cpuinfo_get_l1i_cache(i)->line_size * cpuinfo_get_l1i_cache(i)->partitions * cpuinfo_get_l1i_cache(i)->associativity);
	}
}

TEST(L1I, partitions) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(1, cpuinfo_get_l1i_cache(i)->partitions);
	}
}

TEST(L1I, line_size) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(64, cpuinfo_get_l1i_cache(i)->line_size);
	}
}

TEST(L1I, flags) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_l1i_cache(i)->flags);
	}
}

TEST(L1I, processors) {
	for (uint32_t i = 0; i < cpuinfo_get_l1i_caches_count(); i++) {
		ASSERT_EQ(i, cpuinfo_get_l1i_cache(i)->processor_start);
		ASSERT_EQ(1, cpuinfo_get_l1i_cache(i)->processor_count);
	}
}

TEST(L1D, count) {
	ASSERT_EQ(8, cpuinfo_get_l1d_caches_count());
}

TEST(L1D, non_null) {
	ASSERT_TRUE(cpuinfo_get_l1d_caches());
}

TEST(L1D, size) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(16 * 1024, cpuinfo_get_l1d_cache(i)->size);
	}
}

TEST(L1D, associativity) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(4, cpuinfo_get_l1d_cache(i)->associativity);
	}
}

TEST(L1D, sets) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(cpuinfo_get_l1d_cache(i)->size,
			cpuinfo_get_l1d_cache(i)->sets * cpuinfo_get_l1d_cache(i)->line_size * cpuinfo_get_l1d_cache(i)->partitions * cpuinfo_get_l1d_cache(i)->associativity);
	}
}

TEST(L1D, partitions) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(1, cpuinfo_get_l1d_cache(i)->partitions);
	}
}

TEST(L1D, line_size) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(64, cpuinfo_get_l1d_cache(i)->line_size);
	}
}

TEST(L1D, flags) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_l1d_cache(i)->flags);
	}
}

TEST(L1D, processors) {
	for (uint32_t i = 0; i < cpuinfo_get_l1d_caches_count(); i++) {
		ASSERT_EQ(i, cpuinfo_get_l1d_cache(i)->processor_start);
		ASSERT_EQ(1, cpuinfo_get_l1d_cache(i)->processor_count);
	}
}

TEST(L2, count) {
	ASSERT_EQ(2, cpuinfo_get_l2_caches_count());
}

TEST(L2, non_null) {
	ASSERT_TRUE(cpuinfo_get_l2_caches());
}

TEST(L2, size) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		ASSERT_EQ(256 * 1024, cpuinfo_get_l2_cache(i)->size);
	}
}

TEST(L2, associativity) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		ASSERT_EQ(16, cpuinfo_get_l2_cache(i)->associativity);
	}
}

TEST(L2, sets) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		ASSERT_EQ(cpuinfo_get_l2_cache(i)->size,
			cpuinfo_get_l2_cache(i)->sets * cpuinfo_get_l2_cache(i)->line_size * cpuinfo_get_l2_cache(i)->partitions * cpuinfo_get_l2_cache(i)->associativity);
	}
}

TEST(L2, partitions) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		ASSERT_EQ(1, cpuinfo_get_l2_cache(i)->partitions);
	}
}

TEST(L2, line_size) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		ASSERT_EQ(64, cpuinfo_get_l2_cache(i)->line_size);
	}
}

TEST(L2, flags) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		ASSERT_EQ(0, cpuinfo_get_l2_cache(i)->flags);
	}
}

TEST(L2, processors) {
	for (uint32_t i = 0; i < cpuinfo_get_l2_caches_count(); i++) {
		switch (i) {
			case 0:
				ASSERT_EQ(0, cpuinfo_get_l2_cache(i)->processor_start);
				ASSERT_EQ(4, cpuinfo_get_l2_cache(i)->processor_count);
				break;
			case 1:
				ASSERT_EQ(4, cpuinfo_get_l2_cache(i)->processor_start);
				ASSERT_EQ(4, cpuinfo_get_l2_cache(i)->processor_count);
				break;
		}
	}
}

TEST(L3, none) {
	ASSERT_EQ(0, cpuinfo_get_l3_caches_count());
	ASSERT_FALSE(cpuinfo_get_l3_caches());
}

TEST(L4, none) {
	ASSERT_EQ(0, cpuinfo_get_l4_caches_count());
	ASSERT_FALSE(cpuinfo_get_l4_caches());
}

#include <xperia-c4-dual.h>

int main(int argc, char* argv[]) {
#if CPUINFO_ARCH_ARM
	cpuinfo_set_hwcap(UINT32_C(0x0007B0D6));
	cpuinfo_set_hwcap2(UINT32_C(0x00000000));
#elif CPUINFO_ARCH_ARM64
	cpuinfo_set_hwcap(UINT32_C(0x000000FB));
#endif
	cpuinfo_mock_filesystem(filesystem);
#ifdef __ANDROID__
	cpuinfo_mock_android_properties(properties);
	cpuinfo_mock_gl_renderer("Mali-T760");
#endif
	cpuinfo_initialize();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}