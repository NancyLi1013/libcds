//$$CDS-header$$

#include "map2/map_find_string.h"

namespace map2 {
    CPPUNIT_TEST_SUITE_REGISTRATION( Map_find_string );

    void Map_find_string::generateSequence()
    {
        size_t nPercent = c_nPercentExists;

        if ( nPercent > 100 )
            nPercent = 100;
        else if ( nPercent < 1 )
            nPercent = 1;

        std::vector<std::string> const& arrString = CppUnitMini::TestCase::getTestStrings();
        size_t nSize = arrString.size();
        if ( nSize > c_nMapSize )
            nSize = c_nMapSize;
        m_Arr.resize( nSize );

        nSize = 0;
        for ( size_t i = 0; i < nSize; ++i ) {
            m_Arr[i].pKey = &( arrString[i] );
            m_Arr[i].bExists = CppUnitMini::Rand( 100 ) <= nPercent;
            if ( m_Arr[i].bExists )
                ++nSize;
        }
        c_nMapSize = nSize;
    }

    void Map_find_string::setUpParams( const CppUnitMini::TestCfg& cfg )
    {
        c_nThreadCount = cfg.getSizeT("ThreadCount", c_nThreadCount );
        c_nMapSize = cfg.getSizeT("MapSize", c_nMapSize);
        c_nPercentExists = cfg.getSizeT("PercentExists", c_nPercentExists);
        c_nPassCount = cfg.getSizeT("PassCount", c_nPassCount);
        c_nMaxLoadFactor = cfg.getSizeT("MaxLoadFactor", c_nMaxLoadFactor);
        c_bPrintGCState = cfg.getBool("PrintGCStateFlag", c_bPrintGCState );

        c_nCuckooInitialSize = cfg.getSizeT("CuckooInitialSize", c_nCuckooInitialSize);
        c_nCuckooProbesetSize = cfg.getSizeT("CuckooProbesetSize", c_nCuckooProbesetSize);
        c_nCuckooProbesetThreshold = cfg.getSizeT("CuckooProbesetThreshold", c_nCuckooProbesetThreshold);

        c_nMultiLevelMap_HeadBits = cfg.getSizeT("MultiLevelMapHeadBits", c_nMultiLevelMap_HeadBits);
        c_nMultiLevelMap_ArrayBits = cfg.getSizeT("MultiLevelMapArrayBits", c_nMultiLevelMap_ArrayBits);

        if ( c_nThreadCount == 0 )
            c_nThreadCount = std::thread::hardware_concurrency();

        CPPUNIT_MSG( "Generating test data...");
        cds::OS::Timer    timer;
        generateSequence();
        CPPUNIT_MSG( "   Duration=" << timer.duration() );
        CPPUNIT_MSG( "Map size=" << c_nMapSize << " find key loop=" << m_Arr.size() << " (" << c_nPercentExists << "% success)" );
        CPPUNIT_MSG( "Thread count=" << c_nThreadCount << " Pass count=" << c_nPassCount );

    }
} // namespace map2
