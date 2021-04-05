xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 20;
 1.56116;-0.07529;1.62273;,
 1.56116;-0.07529;-1.44307;,
 1.81618;5.22645;-1.69809;,
 1.81618;5.22645;1.87775;,
 -1.75968;5.22645;-1.69809;,
 -1.75968;5.22645;1.87774;,
 -1.50466;-0.07529;-1.44307;,
 -1.50465;-0.07529;1.62273;,
 -1.24963;-5.37703;1.36771;,
 -1.24964;-5.37703;-1.18805;,
 1.30613;-5.37703;-1.18805;,
 1.30613;-5.37703;1.36772;,
 -1.50466;-0.07529;-1.44307;,
 -1.75968;5.22645;-1.69809;,
 -1.50465;-0.07529;1.62273;,
 -1.75968;5.22645;1.87774;,
 1.30613;-5.37703;1.36772;,
 1.30613;-5.37703;-1.18805;,
 -1.24964;-5.37703;-1.18805;,
 -1.24963;-5.37703;1.36771;;
 
 10;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;8,9,10,11;,
 4;1,12,13,2;,
 4;14,0,3,15;,
 4;16,17,1,0;,
 4;17,18,12,1;,
 4;7,6,9,8;,
 4;19,16,0,14;;
 
 MeshMaterialList {
  13;
  10;
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  10;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.385600;0.524000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.627000;0.000000;0.082000;1.000000;;
   4.000000;
   0.460000;0.460000;0.460000;;
   0.300960;0.000000;0.039360;;
  }
  Material {
   0.586400;0.411200;0.244800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.627000;0.000000;0.082000;1.000000;;
   4.000000;
   0.460000;0.460000;0.460000;;
   0.300960;0.000000;0.039360;;
  }
  Material {
   0.627000;0.000000;0.082000;1.000000;;
   4.000000;
   0.460000;0.460000;0.460000;;
   0.300960;0.000000;0.039360;;
  }
  Material {
   0.800000;0.793600;0.078400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.790400;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.652800;0.348000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.304000;0.153600;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.426400;0.034400;0.034400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.091200;0.091200;0.091200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.476800;0.382400;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  14;
  0.000000;-1.000000;0.000000;,
  0.998845;-0.048046;0.000000;,
  0.000000;1.000000;0.000000;,
  0.998845;-0.048046;-0.000000;,
  -0.998845;-0.048046;0.000003;,
  -0.998845;-0.048046;0.000003;,
  0.000001;-0.048046;-0.998845;,
  0.000001;-0.048046;-0.998845;,
  -0.000002;-0.048045;0.998845;,
  -0.000002;-0.048045;0.998845;,
  0.998845;-0.048046;-0.000000;,
  0.000001;-0.048046;-0.998845;,
  -0.998845;-0.048046;0.000004;,
  -0.000002;-0.048046;0.998845;;
  10;
  4;3,3,1,1;,
  4;2,2,2,2;,
  4;5,5,4,4;,
  4;0,0,0,0;,
  4;6,6,7,7;,
  4;8,8,9,9;,
  4;10,10,3,3;,
  4;11,11,6,6;,
  4;4,4,12,12;,
  4;13,13,8,8;;
 }
 MeshTextureCoords {
  20;
  0.375000;0.125000;,
  0.625000;0.125000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.625000;0.500000;,
  0.375000;0.500000;,
  0.625000;0.625000;,
  0.375000;0.625000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.375000;1.000000;,
  0.875000;0.125000;,
  0.875000;0.250000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.125000;0.000000;;
 }
}
