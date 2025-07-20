#include "Mesh.h"

Mesh::Mesh(const string& filename, float scale): Model(vector<float>(0), true), scale(scale)
{
    Importer importer;
    unsigned int importOptions = aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices| aiProcess_Triangulate| aiProcess_CalcTangentSpace;


    const aiScene* scene = importer.ReadFile(filename, importOptions);

    if (!scene) {
        printf("Error loading mesh from %s: %s\n", filename.c_str(), importer.GetErrorString());
        return;
    }

    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[i];

        vector<Vertex> vertices(mesh->mNumVertices);
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            if (mesh->HasPositions()) {
                vertices[j].Position[0] = mesh->mVertices[j].x;
                vertices[j].Position[1] = mesh->mVertices[j].y;
                vertices[j].Position[2] = mesh->mVertices[j].z;
            }
            if (mesh->HasNormals()) {
                vertices[j].Normal[0] = mesh->mNormals[j].x;
                vertices[j].Normal[1] = mesh->mNormals[j].y;
                vertices[j].Normal[2] = mesh->mNormals[j].z;
            }
            if (mesh->HasTextureCoords(0)) {
                vertices[j].TextureCoords[0] = mesh->mTextureCoords[0][j].x;
                vertices[j].TextureCoords[1] = mesh->mTextureCoords[0][j].y;
            }
            if (mesh->HasTangentsAndBitangents()) {
                vertices[j].Tangent[0] = mesh->mTangents[j].x;
                vertices[j].Tangent[1] = mesh->mTangents[j].y;
                vertices[j].Tangent[2] = mesh->mTangents[j].z;
            }
        }

        vector<int> indices;
        if (mesh->HasFaces()) {
            indices.reserve(mesh->mNumFaces * 3);
            for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                indices.push_back(mesh->mFaces[j].mIndices[0]);
                indices.push_back(mesh->mFaces[j].mIndices[1]);
                indices.push_back(mesh->mFaces[j].mIndices[2]);
            }
        }
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &IBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        vertexCount = static_cast<unsigned int>(indices.size());
        glBindVertexArray(0);
    }
}

void Mesh::draw_model() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

float Mesh::getScale() {
    return scale;
}
