CXXFLAGS = -lfltk -lfltk_gl -lfltk_images `pkg-config --libs glu freealut`
PROGR = playground3

all: playground3

playground3:  readfile.cxx playground3.cxx playground3.h readfile.h
	$(CXX) -Wall readfile.cxx playground3.cxx  -o $@ $(CXXFLAGS)

clean:
	rm -rf $(PROGR) readfile
