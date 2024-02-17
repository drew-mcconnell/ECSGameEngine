build: GameEngine.cpp
	echo "Hello, World"
	clang++ -std=c++17 GameEngine.cpp src/*.cpp -I. -I include -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL_mixer.framework/Versions/A/Headers -F/Library/Frameworks -framework SDL2 -o GameEngine

run:
	./GameEngine

clean:
	rm GameEngine
