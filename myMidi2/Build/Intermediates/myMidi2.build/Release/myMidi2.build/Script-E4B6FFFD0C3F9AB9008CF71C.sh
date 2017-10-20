#!/bin/sh
mkdir -p "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/"
# Copy default icon file into App/Resources
rsync -aved "$ICON_FILE" "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Resources/"
# Copy libfmod and change install directory for fmod to run
rsync -aved ../../../../Downloads/of_v0.9.8_osx_release/libs/fmodex/lib/osx/libfmodex.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Frameworks/";
install_name_tool -change @executable_path/libfmodex.dylib @executable_path/../Frameworks/libfmodex.dylib "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME";
# Copy GLUT framework (must remove for AppStore submissions)
rsync -aved ../../../../Downloads/of_v0.9.8_osx_release/libs/glut/lib/osx/GLUT.framework "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/Frameworks/"

