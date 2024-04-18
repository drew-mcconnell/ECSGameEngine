build: GameEngine.cpp
	echo "Hello, World"
	clang++ -std=c++17 GameEngine.cpp src/*.cpp -I. -I include -I libraries/lua-5.4.6/install/include -I libraries/sol2/include -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Versions/A/Headers -Llibraries/lua-5.4.6/install/lib -llua -F/Library/Frameworks -framework SDL2 -o GameEngine

run:
	./GameEngine

clean:
	rm GameEngine
