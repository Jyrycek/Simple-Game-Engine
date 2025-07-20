#include "Model.h"

Model::Model(const vector<float>& vertices, bool hasTexture)
{
    vertexCount = vertices.size() / (hasTexture ? 8 : 6);
	init_model(vertices, hasTexture);
}

Model::~Model() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Model::init_model(const vector<float>& vertices, bool hasTexture)
{
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, (hasTexture ? 8 : 6) * sizeof(float), (GLvoid*)0);

    glEnableVertexAttribArray(1);

    if (hasTexture) {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(sizeof(float) * 6));
    }
    else {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    }
}

void Model::draw_model() {
	glBindVertexArray(VAO);
	glDrawArrays(drawMode, 0, vertexCount);
}	