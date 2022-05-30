bin = out/test
sources = src/main.cpp
libs =\
ROBOProLib\
KeLibTxt\
MotorIOLib\
TxtControlLib\
SDL\
SDL_gfx\
SDL_ttf\
SDL_image\
ts\
z\
freetype\
png16\
jpeg\
bz2\
asound\
SDLWidgetsLib\

libs := $(patsubst %, -l %, $(libs))

# clang++ --target=arm-linux-gnueabihf -std=c++17 -stdlib=c++

$(bin): $(sources)
	arm-linux-gnueabihf-g++ -MD -std=c++17 $(sources) -o $@ -I txt/include -I src/ -L txt/libs $(libs)

upload: $(bin)
	scp $(bin)  ROBOPro@192.168.7.2:/opt/knobloch/C-Program/test


clean:
	rm $(bin)