
        AC_DEVICE_STRUCT(myQ, "post_buildboundingboxeskernel", boundingBoxes, boundingBoxesSize, float, 6,
          AC_ADD(xyz.x());AC_ADD(xyz.y());
          AC_ADD(xyz.z());AC_ADD(wxyz.x());
          AC_ADD(wxyz.y());AC_ADD(wxyz.z()););
