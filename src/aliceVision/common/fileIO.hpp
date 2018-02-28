// This file is part of the AliceVision project.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#pragma once

#include <aliceVision/structures/Color.hpp>
#include <aliceVision/structures/Matrix3x4.hpp>
#include <aliceVision/structures/Point2d.hpp>
#include <aliceVision/structures/Point3d.hpp>
#include <aliceVision/structures/SeedPoint.hpp>
#include <aliceVision/structures/StaticVector.hpp>
#include <aliceVision/common/MultiViewParams.hpp>

#include <fstream>

namespace aliceVision {
namespace common {

struct MultiViewInputParams;

bool FileExists(const std::string& filePath);
bool FolderExists(const std::string& folderPath);

std::string mv_getFileNamePrefix(const std::string& baseDir, MultiViewInputParams* mip, int index);
std::string mv_getFileName(MultiViewInputParams* mip, int index, EFileType mv_file_type, int scale = 0);
FILE* mv_openFile(MultiViewInputParams* mip, int index, EFileType mv_file_type, const char* readWrite);
Matrix3x4 load3x4MatrixFromFile(FILE* fi);
void memcpyRGBImageFromFileToArr(int camId, Color* imgArr, const std::string& fileNameOrigStr, MultiViewInputParams* mip,
                                 bool transpose, int scaleFactor, int bandType);
struct seed_io_block            // 80 bytes
{
    OrientedPoint op;           // 28 bytes
    Point3d xax;                // 12 bytes
    Point3d yax;                // 12 bytes
    float pixSize;              // 4 bytes
    uint64_t area;              // 8 bytes
    uint64_t segId;             // 8 bytes
    unsigned short ncams;       // 2 bytes
    unsigned short padding[3];  // 6 bytes
};

void saveSeedsToFile(StaticVector<SeedPoint>* seeds, const std::string& fileName);
void saveSeedsToFile(StaticVector<SeedPoint>* seeds, int refImgFileId, MultiViewInputParams* mip, EFileType mv_file_type);
bool loadSeedsFromFile(StaticVector<SeedPoint>** seeds, const std::string& fileName);
bool loadSeedsFromFile(StaticVector<SeedPoint>** seeds, int refImgFileId, MultiViewInputParams* mip, EFileType mv_file_type);
bool getDepthMapInfo(int refImgFileId, MultiViewInputParams* mip, float& mindepth, float& maxdepth,
                     StaticVector<int>** tcams);
bool DeleteDirectory(const std::string& sPath);

} // namespace common
} // namespace aliceVision