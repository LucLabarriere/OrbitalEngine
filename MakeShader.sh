#!/usr/bin/bash
folder=OrbitalEngine/assets/shaders/
cat $folder$1.vert.glsl > $folder$1.glsl
echo "" >> $folder$1.glsl
echo "" >> $folder$1.glsl
cat $folder$1.frag.glsl >> $folder$1.glsl
