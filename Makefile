CXXFLAGS = -lfltk -lfltk_gl -lfltk_images `pkg-config --libs glu freealut`
PROGR = Pacman3d

all: Pacman3d

Pacman3d:  readfile.cxx playground.cxx playground.h readfile.h
	$(CXX) -Wall readfile.cxx playground.cxx  -o $@ $(CXXFLAGS)

clean:
	rm -rf $(PROGR) readfile
