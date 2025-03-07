#pragma once

float cube_vertices_pos_normal[] = 
{
    // Position             Normal             TexCoords
    // Front face
    -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,//  0.0f,  0.0f,  // Bottom-left
     1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f,//  1.0f,  0.0f,  // Bottom-right
    -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,//  0.0f,  1.0f,  // Top-left
     1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f,//  1.0f,  1.0f,  // Top-right
    
    // Back face
    -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,//  0.0f,  0.0f,  // Bottom-left
     1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,//  1.0f,  0.0f,  // Bottom-right
     1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,//  1.0f,  1.0f,  // Top-right
    -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,//  0.0f,  1.0f,  // Top-left

    // Left face
    -1.0f, -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,//  0.0f,  0.0f,  // Bottom-left
    -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,//  1.0f,  0.0f,  // Bottom-right
    -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,//  1.0f,  1.0f,  // Top-right
    -1.0f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,//  0.0f,  1.0f,  // Top-left

    // Right face
     1.0f, -1.0f, 1.0f,  1.0f,  0.0f,  0.0f,//  0.0f,  0.0f,  // Bottom-left
     1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,//  1.0f,  0.0f,  // Bottom-right
     1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,//  1.0f,  1.0f,  // Top-right
     1.0f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,//  0.0f,  1.0f,  // Top-left

     // Top face
     -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,//  0.0f,  0.0f,  // Bottom-left
      1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,//  1.0f,  0.0f,  // Bottom-right
      1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,//  1.0f,  1.0f,  // Top-right
     -1.0f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,//  0.0f,  1.0f,  // Top-left

     // Bottom face
     -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,//  0.0f,  0.0f,  // Bottom-left
      1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,//  1.0f,  0.0f,  // Bottom-right
      1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,//  1.0f,  1.0f,  // Top-right
     -1.0f, -1.0f, 1.0f,  0.0f, -1.0f,  0.0f,//  0.0f,  1.0f   // Top-left
};

unsigned int cube_attribute_offsets[] = 
{
    3, 3
};

unsigned int cube_indices[] = 
{
    // Front face
    0, 1, 2,
    2, 1, 3,

    // Back face
    4, 7, 5,
    5, 7, 6,

    // Left face
    8, 10, 9,
    8, 11, 10,

    // Right face
    12, 13, 15,
    15, 13, 14,

    // Top face
    16, 18, 17,
    18, 16, 19,

    // Bottom face
    20, 21, 22,
    22, 23, 20
};