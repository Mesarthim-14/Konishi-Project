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
 71;
 -36.19320;-271.88089;40.05960;,
 -17.31564;-261.71905;80.08860;,
 -28.00344;-230.16481;67.25880;,
 -48.46116;-235.55485;23.13540;,
 30.12072;-257.10565;96.74077;,
 24.62376;-226.86036;85.55905;,
 76.37064;-260.73925;80.27400;,
 74.10072;-227.57054;67.31640;,
 93.54948;-270.48590;40.34532;,
 96.25585;-231.88009;23.21724;,
 77.65236;-280.64184;0.33528;,
 76.70976;-234.14076;-24.68676;,
 30.55524;-285.26161;-16.33188;,
 20.57892;-236.88324;-44.51328;,
 -16.55292;-281.63450;0.11664;,
 -27.50196;-239.85829;-20.96376;,
 20.57892;-236.88324;-44.51328;,
 30.55524;-285.26161;-16.33188;,
 -82.13052;-109.63537;82.99632;,
 -82.12129;-120.27552;0.00000;,
 20.71716;-137.76840;110.58240;,
 77.90748;-133.66789;75.71796;,
 101.60652;-134.32332;6.17988;,
 78.07284;-152.38417;-73.69068;,
 34.14072;-225.69206;-60.35700;,
 25.48860;-167.00197;-101.86248;,
 76.40520;-163.57561;-81.80557;,
 75.40308;-223.67594;-45.78228;,
 -82.12129;-129.33913;-69.31560;,
 8.80920;-157.04581;-100.97484;,
 -82.16520;-18.91200;161.28492;,
 -82.13052;-81.07848;120.36913;,
 2.85972;-10.36140;149.81544;,
 -82.16520;28.74408;158.03665;,
 39.57216;24.19428;114.91464;,
 66.72180;-30.49080;97.65000;,
 -82.16520;30.25692;-157.09813;,
 14.03676;33.19212;-125.43529;,
 12.37068;-86.42089;-121.45393;,
 -82.12129;-107.12832;-142.35576;,
 86.03064;33.71052;-41.64252;,
 99.08125;27.04692;24.26304;,
 89.56981;-64.66176;-5.78748;,
 78.24276;-70.74744;-76.56588;,
 8.80920;-157.04581;-100.97484;,
 12.37068;-86.42089;-121.45393;,
 78.89988;-67.32060;-86.06845;,
 24.22488;-80.32992;-123.32628;,
 25.60788;18.95124;-126.63072;,
 85.36405;19.38144;-57.08136;,
 9.66540;50.30760;84.79669;,
 -81.85752;50.48268;117.59653;,
 54.40452;51.17040;15.64860;,
 44.59308;48.32724;-34.07100;,
 14.03676;33.19212;-125.43529;,
 -9.53220;45.68760;-119.41044;,
 -82.16520;30.25692;-157.09813;,
 -81.85752;39.76572;-142.57188;,
 -16.55292;-281.63450;0.11664;,
 -9.53220;45.68760;-119.41044;,
 -81.85752;39.76572;-142.57188;,
 -102.46260;-28.48152;86.77308;,
 -102.46260;-3.13116;85.04521;,
 -102.44413;-61.55040;65.00820;,
 -102.29904;8.43252;63.53328;,
 -102.44413;-76.74120;45.12804;,
 -102.29904;2.73168;-74.86128;,
 -102.43932;-82.40125;0.97884;,
 -102.43932;-87.22200;-35.89308;,
 -102.43932;-75.40752;-74.74621;,
 -102.46260;-2.32644;-82.58832;;
 
 70;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;8,9,7,6;,
 4;10,11,9,8;,
 4;12,13,11,10;,
 4;14,15,16,17;,
 4;14,0,3,15;,
 4;18,19,3,2;,
 4;18,2,5,20;,
 4;20,5,7,21;,
 4;21,7,9,22;,
 4;11,23,22,9;,
 4;24,25,26,27;,
 4;28,29,16,15;,
 4;19,28,15,3;,
 3;30,31,32;,
 3;33,30,32;,
 4;34,33,32,35;,
 4;20,32,31,18;,
 4;20,21,35,32;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;41,34,35,42;,
 4;39,38,29,28;,
 4;35,21,22,42;,
 4;22,23,43,42;,
 4;23,44,45,43;,
 4;46,47,48,49;,
 4;33,34,50,51;,
 4;34,41,52,50;,
 4;41,40,53,52;,
 4;40,54,55,53;,
 4;54,56,57,55;,
 4;13,44,25,24;,
 4;44,23,26,25;,
 4;23,11,27,26;,
 4;11,13,24,27;,
 4;43,45,47,46;,
 4;45,54,48,47;,
 4;54,40,49,48;,
 4;40,43,46,49;,
 3;8,6,10;,
 3;10,6,12;,
 3;6,4,12;,
 3;12,4,58;,
 3;4,1,14;,
 3;1,0,14;,
 3;52,53,50;,
 3;53,55,50;,
 3;50,55,51;,
 3;59,60,51;,
 3;61,62,63;,
 3;62,64,63;,
 3;63,64,65;,
 3;64,66,65;,
 3;65,66,67;,
 3;67,66,68;,
 3;68,66,69;,
 3;66,70,69;,
 4;18,31,63,65;,
 4;31,30,61,63;,
 4;30,33,62,61;,
 4;33,51,64,62;,
 4;51,60,66,64;,
 4;60,36,70,66;,
 4;36,39,69,70;,
 4;39,28,68,69;,
 4;28,19,67,68;,
 4;19,18,65,67;;
 
 MeshMaterialList {
  1;
  70;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "pattern.png";
   }
  }
 }
 MeshNormals {
  83;
  -0.903253;-0.426364;0.048458;,
  -0.725833;-0.570042;-0.384991;,
  0.298241;0.447168;0.843263;,
  -0.694006;-0.132547;0.707663;,
  0.033578;0.059839;0.997643;,
  0.712060;0.099258;0.695067;,
  0.998140;-0.050168;0.034645;,
  0.786251;-0.398281;-0.472421;,
  -0.121218;-0.633558;-0.764140;,
  -0.665619;-0.504101;-0.550303;,
  -0.737568;-0.442903;0.509736;,
  0.125976;-0.307334;0.943226;,
  0.773748;-0.047206;0.631732;,
  0.999527;0.012023;0.028320;,
  0.845714;0.053243;-0.530974;,
  -0.093015;-0.541949;-0.835248;,
  -0.672930;0.083721;0.734953;,
  -0.003013;0.337224;0.941419;,
  0.670681;0.290343;0.682560;,
  0.999505;-0.014755;0.027784;,
  0.683298;-0.342024;-0.645076;,
  -0.004481;-0.500865;-0.865514;,
  -0.629234;-0.493455;-0.600472;,
  -0.940824;-0.335834;0.045452;,
  -0.955287;-0.290272;0.056289;,
  -0.031955;-0.558322;0.829008;,
  0.249547;-0.194136;0.948703;,
  0.242172;0.395702;-0.885874;,
  0.265064;0.354520;-0.896692;,
  0.116370;-0.415275;-0.902222;,
  0.219523;-0.421209;-0.879996;,
  0.954720;0.161247;-0.250017;,
  0.991930;-0.002951;0.126755;,
  0.576142;0.579093;0.576812;,
  0.781502;0.086047;0.617941;,
  0.996141;0.051749;0.070887;,
  0.899390;-0.253005;-0.356491;,
  0.154101;-0.250188;0.955855;,
  0.107230;0.983338;0.146794;,
  0.257423;0.963920;0.067765;,
  0.163830;0.981492;-0.099165;,
  0.084308;0.975955;-0.201007;,
  0.045803;0.936624;-0.347329;,
  0.040399;0.988151;0.148075;,
  0.053581;-0.700459;-0.711678;,
  -0.027446;-0.573346;-0.818853;,
  0.328243;-0.500051;-0.801377;,
  0.273930;-0.711973;-0.646573;,
  0.290823;0.017635;-0.956614;,
  0.920581;-0.013214;-0.390329;,
  0.441078;0.224629;-0.868903;,
  0.860364;0.199967;-0.468814;,
  -0.989843;-0.098603;0.102411;,
  -0.985585;-0.158319;0.059637;,
  -0.981598;-0.056496;0.182409;,
  -0.992084;0.075556;0.100303;,
  -0.988210;0.151275;0.023584;,
  -0.994262;0.104823;-0.021314;,
  -0.987617;0.077504;-0.136407;,
  -0.990813;-0.098447;-0.092728;,
  -0.976965;-0.213054;-0.012139;,
  -0.969430;-0.243345;0.031454;,
  0.417538;0.900750;0.119627;,
  0.369235;0.914985;-0.162690;,
  0.338468;0.903514;-0.262872;,
  0.277811;0.536444;-0.796900;,
  0.992170;-0.075964;-0.099137;,
  0.401832;-0.869930;-0.285926;,
  0.011412;-0.970270;0.241754;,
  0.010283;-0.970293;0.241713;,
  0.010521;-0.970283;0.241743;,
  0.009701;-0.970308;0.241679;,
  0.009661;-0.970309;0.241677;,
  0.009640;-0.970303;0.241701;,
  0.009627;-0.970297;0.241725;,
  0.009744;-0.970296;0.241726;,
  -0.934964;-0.244836;0.256704;,
  -0.958636;-0.084078;0.271935;,
  -0.967526;0.149688;0.203681;,
  -0.926779;0.370400;0.062323;,
  -0.929383;0.359435;-0.083984;,
  -0.970050;0.114922;-0.213999;,
  -0.960420;-0.198373;-0.195552;;
  70;
  4;24,16,3,23;,
  4;16,17,4,3;,
  4;17,18,5,4;,
  4;19,6,5,18;,
  4;20,7,6,19;,
  4;21,8,7,20;,
  4;22,9,8,21;,
  4;22,24,23,9;,
  4;10,0,23,3;,
  4;10,3,4,11;,
  4;11,4,5,12;,
  4;12,5,6,13;,
  4;7,14,13,6;,
  4;44,45,46,47;,
  4;1,15,8,9;,
  4;0,1,9,23;,
  3;37,25,26;,
  3;2,37,26;,
  4;33,2,26,34;,
  4;11,26,25,10;,
  4;11,12,34,26;,
  4;27,28,30,29;,
  4;31,32,35,36;,
  4;32,33,34,35;,
  4;29,30,15,1;,
  4;34,12,13,35;,
  4;13,14,36,35;,
  4;14,15,30,36;,
  4;49,48,50,51;,
  4;2,33,38,43;,
  4;33,62,39,38;,
  4;62,63,40,39;,
  4;63,64,41,40;,
  4;28,27,42,41;,
  4;8,15,45,44;,
  4;65,14,65,65;,
  4;14,7,66,66;,
  4;7,8,44,47;,
  4;36,30,67,67;,
  4;30,28,50,48;,
  4;28,31,51,50;,
  4;31,36,49,51;,
  3;68,69,70;,
  3;70,69,71;,
  3;69,72,71;,
  3;71,72,73;,
  3;72,74,73;,
  3;74,75,73;,
  3;39,40,38;,
  3;40,41,38;,
  3;38,41,43;,
  3;41,42,43;,
  3;54,55,52;,
  3;55,56,52;,
  3;52,56,53;,
  3;56,57,53;,
  3;53,57,61;,
  3;61,57,60;,
  3;60,57,59;,
  3;57,58,59;,
  4;10,76,52,53;,
  4;76,77,54,52;,
  4;77,78,55,54;,
  4;78,79,56,55;,
  4;79,80,57,56;,
  4;80,81,58,57;,
  4;81,82,59,58;,
  4;82,1,60,59;,
  4;1,0,61,60;,
  4;0,10,53,61;;
 }
 MeshTextureCoords {
  71;
  0.616937;0.974421;,
  0.533889;0.945147;,
  0.562791;0.854249;,
  0.679112;0.869776;,
  0.451960;0.931857;,
  0.455401;0.844729;,
  0.378965;0.942325;,
  0.367371;0.846775;,
  0.314803;0.970402;,
  0.287669;0.859190;,
  0.250687;0.999659;,
  0.200447;0.865702;,
  0.171876;1.012967;,
  0.068921;0.873602;,
  0.748879;1.002518;,
  0.853658;0.882173;,
  1.068921;0.873602;,
  1.171876;1.012967;,
  0.624166;0.507037;,
  0.750000;0.537689;,
  0.470525;0.588081;,
  0.372732;0.576268;,
  0.259668;0.578156;,
  0.129594;0.630185;,
  0.081929;0.841364;,
  0.039023;0.672294;,
  0.119570;0.662424;,
  0.163153;0.835556;,
  0.861574;0.563798;,
  1.013850;0.643613;,
  0.574989;0.245689;,
  0.595296;0.424773;,
  0.496962;0.221057;,
  0.576307;0.108405;,
  0.447217;0.121512;,
  0.404601;0.279044;,
  0.923304;0.104047;,
  1.017736;0.095592;,
  1.016155;0.440163;,
  0.916724;0.499815;,
  0.178253;0.094098;,
  0.288222;0.113294;,
  0.239731;0.377481;,
  0.126724;0.395012;,
  0.013850;0.643613;,
  0.016155;0.440163;,
  0.118088;0.385140;,
  0.030870;0.422617;,
  0.031757;0.136616;,
  0.156195;0.135376;,
  0.481937;0.046287;,
  0.596781;0.045783;,
  0.294575;0.043801;,
  0.146163;0.051992;,
  0.017736;0.095592;,
  -0.012678;0.059596;,
  -0.076696;0.104047;,
  -0.082951;0.076655;,
  -0.251121;1.002518;,
  0.987322;0.059596;,
  0.917049;0.076655;,
  0.638165;0.273256;,
  0.639741;0.200229;,
  0.660005;0.368518;,
  0.661548;0.166917;,
  0.683961;0.412279;,
  0.850545;0.183340;,
  0.748479;0.428584;,
  0.803638;0.442471;,
  0.850325;0.408437;,
  0.857972;0.197911;;
 }
}
