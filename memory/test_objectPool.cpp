
#include "objectPool.hpp"

#include <cassert>
#include <cstring>
#include <vector>

void RunTinyTests();

void test_AssetFactory_DefaultCreateExpectValidAssetPtr() {
    AssetFactory af{};
    auto assetPtr = af.create("doom", "/shared/doom.dat");
    assert(assetPtr);
}

void test_AssetFactory_DeleteNonExistingAssetExceptNoEffect() {
    AssetFactory af{};
    auto pAsset = af.create("", "");
    assert(! af.del(pAsset + 0x10));
}

void test_AssetFactory_DeleteExistingAsset() {
    AssetFactory af{};
    auto assetPtr = af.create("doom", "/shared/doom.dat");
    assert(af.del(assetPtr));
}

void test_AssetFactory_AssetHasUniqueId() {
    AssetFactory af{};
    auto impPtr = af.create("imp", "/shared/imp.dat");
    auto lostSoulPtr = af.create("lostSoul", "/shared/lostSoul.dat");
    assert(impPtr->id() != lostSoulPtr->id());
}

void test_AssetFactory_FailToCreateIfObjectPoolIsFull() {
    AssetFactory af{};
    af.create("imp", "/shared/imp.dat");
    af.create("imp", "/shared/imp.dat");
    af.create("imp", "/shared/imp.dat");
    af.create("imp", "/shared/imp.dat");
    auto impPtr = af.create("imp", "/shared/imp.dat");
    assert(! impPtr);
}

void test_AssetFactory_ReuseIdAfterDeletion() {
    AssetFactory af{};
    auto pAsset = af.create("imp", "/shared/imp.dat");
    auto oldId = pAsset->id();
    af.del(pAsset);
    auto pAssetNew = af.create("shotgunZombie", "/share/shotgunZombie.dat");
    assert(oldId == pAssetNew->id());
}

void test_AssetFactory_FillEmptyHoles() {
    AssetFactory af{};
    auto pAsset1 = af.create("imp", "/shared/imp.dat");
    auto pAsset2 = af.create("imp", "/shared/imp.dat");
    auto pAsset3 = af.create("imp", "/shared/imp.dat");
    auto pAsset4 = af.create("imp", "/shared/imp.dat");
    auto id2 = pAsset2->id();
    af.del(pAsset2);
    auto pAsset5 = af.create("", "");
    assert(id2 == pAsset5->id());
}

void test_Asset_ExpectNameProperty() {
    AssetFactory af{};
    auto assetPtr = af.create("doom", "/shared/doom.dat");
    assert(
      0 == std::strcmp(assetPtr->name().c_str(), "doom")
    );
}

void test_Asset_ExpectPathProperty() {
    AssetFactory af{};
    auto assetPtr = af.create("doom", "/shared/doom.dat");
    assert(
      0 == std::strcmp(assetPtr->path().c_str(), "/shared/doom.dat")
    );
}

void test_Asset_ExpectValidAssetId() {
    AssetFactory af{};
    auto assetPtr = af.create("doom", "/shared/doom.dat");
    assert(AssetConstants::InvalidId != assetPtr->id());
}

int main(int argc, char **argv) {
    RunTinyTests();
    return 0;
}