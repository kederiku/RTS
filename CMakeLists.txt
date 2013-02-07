CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

PROJECT(id_dtc)

ADD_SUBDIRECTORY(uilibgp2016)

SET(EXECUTABLE_OUTPUT_PATH .)

SET(CMAKE_CXX_FLAGS_DEBUG "-g3 -DD_ERRORS_ON")

SET(srcs
	src/astar.cpp
	src/buffer.cpp
	src/building/academy.cpp
	src/building/archery_range.cpp
	src/building/barrack.cpp
	src/building/building.cpp
	src/building/house.cpp
	src/building/stable.cpp
	src/building/temple.cpp
	src/building/tower.cpp
	src/building/town_center.cpp
	src/building_interface.cpp
	src/case_map.cpp
	src/client.cpp
	src/connection.cpp
	src/container_game.cpp
	src/game.cpp
	src/ressource.cpp
	src/info.cpp
	src/interface.cpp
	src/list_node.cpp
	src/main.cpp
	src/map.cpp
	src/map_editor.cpp
	src/menu.cpp
	src/menu_game.cpp
	src/mutex.cpp
	src/my_popup.cpp
	src/nation.cpp
	src/network.cpp
	src/node.cpp
	src/player.cpp
	src/point.cpp
	src/server.cpp
	src/state.cpp
	src/ressources.cpp
	src/msg.cpp
	src/tools.cpp
	src/ui.cpp
	src/unit/archer.cpp
	src/unit/druide.cpp
	src/unit/knight.cpp
	src/unit/mage.cpp
	src/unit/peon.cpp
	src/unit/unit.cpp
	src/unit/warrior.cpp
	src/user.cpp
	src/inter.cpp)

FIND_PACKAGE(SDL REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(SDL_ttf REQUIRED)
LINK_DIRECTORIES(uilibgp2016 uilibgp2016/lib)
INCLUDE_DIRECTORIES(uilibgp2016/include uilibgp2016/tools ${SDL_INCLUDE_DIR} ${SDLTTF_INCLUDE_DIR} include)
ADD_DEFINITIONS(-W -Wall -Werror -DD_SDL
		-DSRC_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${srcs})
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} 2D cmc ${SDL_LIBRARY} ${SDLTTF_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

IF (UNIX)
	ADD_CUSTOM_TARGET(distclean COMMENT "Distcleaning lib2D")
	ADD_CUSTOM_COMMAND(COMMAND rm ARGS -rf ${objs} ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_PROJECT_NAME} TARGET distclean)

	ADD_CUSTOM_TARGET(rebuild COMMENT "Rebuilding lib2D")
	ADD_CUSTOM_COMMAND(COMMAND make ARGS distclean TARGET rebuild)
	ADD_CUSTOM_COMMAND(COMMAND make TARGET rebuild)

	ADD_CUSTOM_TARGET(release COMMENT "Releasing lib2D")
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Release TARGET release)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS distclean TARGET release)
	ADD_CUSTOM_COMMAND(COMMAND make TARGET release)

	ADD_CUSTOM_TARGET(debug COMMENT "Debugging lib2D")
	ADD_CUSTOM_COMMAND(COMMAND cmake ARGS . -DCMAKE_BUILD_TYPE:STRING=Debug TARGET debug)
	ADD_CUSTOM_COMMAND(COMMAND make ARGS distclean TARGET debug)
	ADD_CUSTOM_COMMAND(COMMAND make TARGET debug)
ENDIF(UNIX)
