#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Camera* camera) : camera(camera) {
	camera->addObserver(this);
}

ShaderProgram::~ShaderProgram() {
	delete camera;
}

void ShaderProgram::initShader(const char* vertexFile, const char* fragmentFile) {
	this->shaderProgramID = loadShader(vertexFile, fragmentFile);
	if (shaderProgramID == 0) {
		cerr << "Failed to load shaders!" << endl;
		exit(EXIT_FAILURE);
	}
}

void ShaderProgram::use(Texture * texture) {
	glUseProgram(shaderProgramID);

	setViewMatrix(camera->getViewMatrix());
	setLights();

	if (useTexture) {
		setTexture(0, texture->getScale());
		glUniform1i(glGetUniformLocation(shaderProgramID, "useTexture"), 1);
	}
	else {
		glUniform1i(glGetUniformLocation(shaderProgramID, "useTexture"), 0);
	}
}

void ShaderProgram::unbind() {
	glUseProgram(0);
}

void ShaderProgram::setLights() {
	int numberOfLights = lights.size();

	glUniform1i(glGetUniformLocation(shaderProgramID, "numberOfLights"), numberOfLights);

	for (int i = 0; i < numberOfLights; i++) {
		string prefix = "lights[" + std::to_string(i) + "].";

		glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "position").c_str()), 1, value_ptr(lights[i]->getPosition()));
		glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "lightColor").c_str()), 1, value_ptr(lights[i]->getColor()));
		glUniform1f(glGetUniformLocation(shaderProgramID, (prefix + "lightIntensity").c_str()), lights[i]->getIntensity());

		glUniform1f(glGetUniformLocation(shaderProgramID, (prefix + "constantAttenuation").c_str()), lights[i]->getConstantAttenuation());
		glUniform1f(glGetUniformLocation(shaderProgramID, (prefix + "linearAttenuation").c_str()), lights[i]->getLinearAttenuation());
		glUniform1f(glGetUniformLocation(shaderProgramID, (prefix + "quadraticAttenuation").c_str()), lights[i]->getQuadraticAttenuation());

		int type = static_cast<int>(lights[i]->getType());
		glUniform1i(glGetUniformLocation(shaderProgramID, (prefix + "type").c_str()), type);

		if (type == DIRECTIONAL) {
			glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "direction").c_str()), 1, value_ptr(lights[i]->getDirection()));
		}
		else if (type == SPOT) {
			SpotLight* spotlight = dynamic_cast<SpotLight*>(lights[i]);
			if (spotlight) {
				glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "position").c_str()), 1, value_ptr(camera->getPosition()));
				glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "direction").c_str()), 1, value_ptr(camera->getFront()));
			}
			else {
				glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "position").c_str()), 1, value_ptr(lights[i]->getPosition()));
				glUniform3fv(glGetUniformLocation(shaderProgramID, (prefix + "direction").c_str()), 1, value_ptr(lights[i]->getDirection()));
			}
			glUniform1f(glGetUniformLocation(shaderProgramID, (prefix + "cutAngle").c_str()), lights[i]->getAngle());
		}
	}
}

void ShaderProgram::setProjectionMatrix() {
	mat4 projection2 = Window::getInstance().getProjectionMatrix();

	GLuint location = glGetUniformLocation(shaderProgramID, "projectionMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(projection2));
}

void ShaderProgram::setModelMatrix(mat4& modelMatrix) {
	GLuint location = glGetUniformLocation(shaderProgramID, "modelMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelMatrix));
}

void ShaderProgram::setViewMatrix(const mat4& viewMatrix) {
	GLuint location = glGetUniformLocation(shaderProgramID, "viewMatrix");
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(viewMatrix));
}

void ShaderProgram::updateViewMatrix(const mat4& viewMatrix) {
	setViewMatrix(viewMatrix);
}

void ShaderProgram::addLight(Light* light) {
	this->lights.push_back(light);
}

void ShaderProgram::setMaterial(Material* material) {
	glUniform3fv(glGetUniformLocation(shaderProgramID, "material.ambient"), 1, value_ptr(material->getAmbient()));
	glUniform3fv(glGetUniformLocation(shaderProgramID, "material.diffuse"), 1, value_ptr(material->getDiffuse()));
	glUniform3fv(glGetUniformLocation(shaderProgramID, "material.specular"), 1, value_ptr(material->getSpecular()));
	glUniform1f(glGetUniformLocation(shaderProgramID, "material.shininess"), material->getShininess());
}

void ShaderProgram::setTexture(int textureUnit, float uvRepeat) {
	glUniform1i(glGetUniformLocation(shaderProgramID, "textureSampler"), textureUnit);
	glUniform1f(glGetUniformLocation(shaderProgramID, "uvRepeat"), uvRepeat);
}

void ShaderProgram::setSkyboxTexture() {
	glUniform1i(glGetUniformLocation(shaderProgramID, "skybox"), 0);
}

void ShaderProgram::setShaderStatic(bool isStatic) {
	glUniform1i(glGetUniformLocation(shaderProgramID, "isStatic"), isStatic ? 1 : 0);
}
