#deepin-gomoku
Gomoku is an easy and funny chess game that is suitable for all ages.
五子棋是一款容易上手，老少皆宜，而且趣味横生，引人入胜的棋类小游戏。

#Core
The GUI is based on DTK, Qt (Supported >= 5.12).

Build-Depends: debhelper (>= 11),cmake, pkg-config, qtbase5-dev, qtchooser (>= 55-gc9562a1-1~),qt5-qmake, libdtkwidget-dev, qttools5-dev-tools, libqt5svg5-dev, qttools5-dev,libgtest-dev, libgmock-dev

#Installation
sudo apt-get install deepin-gomoku

#Build
mkdir build
cd build
cmake ..
make
make install
