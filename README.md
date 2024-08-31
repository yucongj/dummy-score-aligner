# Dummy score aligner

This is the starter code for developing audio-to-score alignment plugins for the host application [*Piano Precision*](https://github.com/yucongj/piano-precision). 

Please make sure you can run the build script first, e.g., `make -f Makefile.osx`. To install the package on Mac, e.g., copy `dummy-aligner.dylib` to the directory `$HOME/Library/Audio/Plug-Ins/Vamp/AudioToScoreAlignment/` (please create the folder `AudioToScoreAlignment` if it doesn't already exist).


To implement new audio-to-score alignment algorithm in the plugin, please follow the instructions here: [Developing Vamp aligner plugins](https://github.com/yucongj/piano-precision?tab=readme-ov-file#developing-vamp-aligner-plugins).

