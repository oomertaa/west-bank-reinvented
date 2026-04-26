CXX = g++
CXXFLAGS = -I include
SRC = main.cpp src/Game.cpp src/LevelConfig.cpp src/Player.cpp src/Entity.cpp src/Weapon.cpp \
      src/Pistol.cpp src/Shotgun.cpp src/Rifle.cpp src/Thief.cpp src/Shop.cpp
OUT = westbank.exe

all:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	del $(OUT)
