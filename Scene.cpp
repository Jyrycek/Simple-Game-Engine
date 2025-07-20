#include "Scene.h"
#include "Mesh.h"

Scene::Scene()
{
	camera = new Camera(vec3(0.0f, 0.5f, 5.0f), vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
	controls = new Controls(camera);
}

Scene::~Scene()
{
	delete& drawableObjects;
	delete controls;
	delete camera;
}

void Scene::CreateForestScene() {
	vector<float> bushVertices(bushes, bushes + sizeof(bushes) / sizeof(bushes[0]));

	vector<vec3> controlPoints = {
	vec3(-2.0f, 2.0f, -2.0f),
	vec3(-1.0f, 5.0f, -1.0f),
	vec3(1.0f, 5.0f, 1.0f),
	vec3(2.0f, 2.0f, 2.0f)
	};

	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	ShaderProgram* shaderProgram2 = new ShaderProgram(camera);
	ShaderProgram* shaderProgram3 = new ShaderProgram(camera);

	shaderProgram->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	shaderProgram2->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	shaderProgram3->initShader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	shaderProgram->setUseTexture(true);
	shaderProgram2->setUseTexture(false);
	shaderProgram3->setUseTexture(false);

	Texture* house_texture = new Texture("Models/house.png", 1.0);
	Texture* poop_texture = new Texture("Models/image_0.png", 1.0);
	Texture* wood_texture = new Texture("Models/wooden_fence.png", 1.0);
	Texture* plain_texture = new Texture("Models/grass.png", 1.0);
	Texture* tree_texture = new Texture("Models/tree.png", 1.0);

	Mesh* plain_model = new Mesh("Models/teren.obj", 1.0);
	Mesh* poop_model = new Mesh("Models/poop.fbx", 1.0f);
	Mesh* house_model = new Mesh("Models/house.obj", 1.0f);
	Mesh* tree_model = new Mesh("Models/tree.obj", 1.0f);
	Model* bush_model = new Model(bushVertices, false);

	Material* material = new Material(vec3(0.2f, 0.2f, 0.2f), vec3(0.8f, 0.8f, 0.8f), vec3(1.0f, 1.0f, 1.0f), 32.0f);
	Material* tree_material = new Material(vec3(0.1f, 0.1f, 0.1f), vec3(0.1f, 0.3f, 0.1f), vec3(0.02f, 0.02f, 0.02f), 5.0f);
	Material* bush_material = new Material(vec3(0.01f, 0.01f, 0.01f), vec3(0.1f, 0.2f, 0.1f), vec3(0.02f, 0.02f, 0.02f), 3.0f);
	Material* material_sun = new Material(vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), vec3(1.0f, 1.0f, 1.0f), 0.0f);

	DrawableObject* plain_object = new DrawableObject(camera, plain_model, shaderProgram, material, plain_texture);
	plain_object->translate(0.0f, -1.0f, 0.0f);
	plain_object->scale(plain_texture->getScale());
	drawableObjects.push_back(plain_object);

	DrawableObject* house_object = new DrawableObject(camera, house_model, shaderProgram, material, house_texture);
	house_object->translate(-6.0f, -1.0f, -6.0f);
	house_object->scale(0.2);
	drawableObjects.push_back(house_object);

	Light* light2 = new Light(vec3(0.0f, 4.0f, 4.0f), vec3(0.385f, 0.647f, 0.812f));
	light2->setType(POINT);
	shaderProgram2->addLight(light2);
	shaderProgram->addLight(light2);

	treeShaderProgram = shaderProgram;
	this->treeModel = tree_model;
	this->treeMaterial = tree_material;
	this->treeTexture = tree_texture;

	for (int i = 0; i < 50; ++i) {
		DrawableObject* tree = new DrawableObject(camera, tree_model, shaderProgram, tree_material, tree_texture);
		RandomTransform(tree, i);
		drawableObjects.push_back(tree);

		DrawableObject* bush = new DrawableObject(camera, bush_model, shaderProgram2, bush_material, nullptr);
		RandomTransform2(bush, i);
		drawableObjects.push_back(bush);
	}

	vector<string> skyboxTextures = {
	"cubemap/posx.jpg", "cubemap/negx.jpg",
	"cubemap/posy.jpg", "cubemap/negy.jpg",
	"cubemap/posz.jpg", "cubemap/negz.jpg"
	};

	ModelSkybox* skybox = new ModelSkybox(skyboxTextures);
	skybox->setStatic(false);
	this->skybox_model = skybox;
	ShaderProgram* skyboxShader = new ShaderProgram(camera);
	skyboxShader->initShader("Shaders/skybox_vertex.glsl", "Shaders/skybox_fragment.glsl");
	DrawableObject* skyboxDrawable = new DrawableObject(camera, skybox, skyboxShader, nullptr, nullptr);
	this->skybox = skyboxDrawable;

	vector<float> spherevertices(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	Model* sphere_model = new Model(spherevertices, false);

	DrawableObject* sphere_object = new DrawableObject(camera, sphere_model, shaderProgram3, material_sun, nullptr);
	sphere_object->translate(0.0f, 4.0f, 4.0f);
	sphere_object->scale(0.4f);
	drawableObjects.push_back(sphere_object);
}

void Scene::CreateFourSpheres() {
	Light* light = new Light(vec3(0.0f, 0.0f, 1.0f), vec3(0.385f, 0.647f, 0.812f));

	ShaderProgram* shaderProgram_sphere = new ShaderProgram(camera);
	shaderProgram_sphere->addLight(light);
	shaderProgram_sphere->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");

	vector<float> spherevertices(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	Model* sphere_model = new Model(spherevertices, false);

	Material* material1 = new Material(vec3(0.1f, 0.1f, 0.3f), vec3(0.3f, 0.3f, 0.7f), vec3(0.5f, 0.5f, 0.9f), 52.0f);
	Material* material2 = new Material(vec3(0.3f, 0.1f, 0.1f), vec3(0.7f, 0.3f, 0.3f), vec3(0.9f, 0.5f, 0.5f), 16.0f);
	Material* material3 = new Material(vec3(0.1f, 0.3f, 0.1f), vec3(0.3f, 0.7f, 0.3f), vec3(0.5f, 0.9f, 0.5f), 8.0f);
	Material* material4 = new Material(vec3(0.3f, 0.3f, 0.1f), vec3(0.7f, 0.7f, 0.3f), vec3(0.9f, 0.9f, 0.5f), 4.0f);

	DrawableObject* sphere_object1 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material1, nullptr);
	sphere_object1->translate(-0.4f, 0.0f, 0.0f);
	sphere_object1->scale(0.12f);
	drawableObjects.push_back(sphere_object1);

	DrawableObject* sphere_object2 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material2, nullptr);
	sphere_object2->translate(0.0f, 0.4f, 0.0f);
	sphere_object2->scale(0.12f);
	drawableObjects.push_back(sphere_object2);

	DrawableObject* sphere_object3 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material3, nullptr);
	sphere_object3->translate(0.0f, -0.4f, 0.0f);
	sphere_object3->scale(0.12f);
	drawableObjects.push_back(sphere_object3);

	DrawableObject* sphere_object4 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material4, nullptr);
	sphere_object4->translate(0.4f, 0.0f, 0.0f);
	sphere_object4->scale(0.12f);
	drawableObjects.push_back(sphere_object4);
}

void Scene::CreateFourSpheresDirectional() {
	Light* light = new Light(vec3(0.0f, 0.0f, 0.0f), vec3(0.385f, 0.647f, 0.812f));
	vec3 dir = vec3(0.5f, 0.0f, 0.0f);
	light->setDirection(dir);
	light->setType(DIRECTIONAL);

	ShaderProgram* shaderProgram_sphere = new ShaderProgram(camera);
	shaderProgram_sphere->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	shaderProgram_sphere->addLight(light);

	vector<float> spherevertices(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	Model* sphere_model = new Model(spherevertices, false);

	Material* material1 = new Material(vec3(0.1f, 0.1f, 0.3f), vec3(0.3f, 0.3f, 0.7f), vec3(0.5f, 0.5f, 0.9f), 52.0f);
	Material* material2 = new Material(vec3(0.3f, 0.1f, 0.1f), vec3(0.7f, 0.3f, 0.3f), vec3(0.9f, 0.5f, 0.5f), 16.0f);
	Material* material3 = new Material(vec3(0.1f, 0.3f, 0.1f), vec3(0.3f, 0.7f, 0.3f), vec3(0.5f, 0.9f, 0.5f), 8.0f);
	Material* material4 = new Material(vec3(0.3f, 0.3f, 0.1f), vec3(0.7f, 0.7f, 0.3f), vec3(0.9f, 0.9f, 0.5f), 4.0f);

	DrawableObject* sphere_object1 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material1, nullptr);
	sphere_object1->translate(-0.4f, 0.0f, 0.0f);
	sphere_object1->scale(0.12f);
	drawableObjects.push_back(sphere_object1);

	DrawableObject* sphere_object2 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material2, nullptr);
	sphere_object2->translate(0.0f, 0.4f, 0.0f);
	sphere_object2->scale(0.12f);
	drawableObjects.push_back(sphere_object2);

	DrawableObject* sphere_object3 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material3, nullptr);
	sphere_object3->translate(0.0f, -0.4f, 0.0f);
	sphere_object3->scale(0.12f);
	drawableObjects.push_back(sphere_object3);

	DrawableObject* sphere_object4 = new DrawableObject(camera, sphere_model, shaderProgram_sphere, material4, nullptr);
	sphere_object4->translate(0.4f, 0.0f, 0.0f);
	sphere_object4->scale(0.12f);
	drawableObjects.push_back(sphere_object4);
}

void Scene::CreateForestDarkScene() {
	vector<float> bushVertices(bushes, bushes + sizeof(bushes) / sizeof(bushes[0]));

	ShaderProgram* shaderProgram = new ShaderProgram(camera);
	ShaderProgram* shaderProgram2 = new ShaderProgram(camera);

	shaderProgram->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	shaderProgram2->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	shaderProgram->setUseTexture(true);
	shaderProgram2->setUseTexture(false);

	Texture* house_texture = new Texture("Models/house.png", 1.0);
	Texture* poop_texture = new Texture("Models/image_0.png", 1.0);
	Texture* wood_texture = new Texture("Models/wooden_fence.png", 1.0);
	Texture* plain_texture = new Texture("Models/grass.png", 1.0);
	Texture* tree_texture = new Texture("Models/tree.png", 1.0);

	Mesh* plain_model = new Mesh("Models/teren.obj", 1.0);
	Mesh* poop_model = new Mesh("Models/poop.fbx", 1.0f);
	Mesh* house_model = new Mesh("Models/house.obj", 1.0f);
	Mesh* tree_model = new Mesh("Models/tree.obj", 1.0f);
	Model* bush_model = new Model(bushVertices, false);

	Material* material = new Material(vec3(0.02f, 0.02f, 0.02f), vec3(0.7f, 0.4f, 0.2f), vec3(0.6f, 0.5f, 0.4f), 10.0f);
	Material* tree_material = new Material(vec3(0.01f, 0.01f, 0.01f), vec3(0.4f, 0.2f, 0.3f), vec3(0.1f, 0.1f, 0.1f), 4.0f);
	Material* bush_material = new Material(vec3(0.005f, 0.005f, 0.005f), vec3(0.2f, 0.4f, 0.2f), vec3(0.1f, 0.1f, 0.1f), 3.0f);


	DrawableObject* plain_object = new DrawableObject(camera, plain_model, shaderProgram, material, plain_texture);
	plain_object->translate(0.0f, -1.0f, 0.0f);
	plain_object->scale(plain_texture->getScale());
	drawableObjects.push_back(plain_object);

	DrawableObject* poop_object = new DrawableObject(camera, poop_model, shaderProgram, material, poop_texture);
	poop_object->translate(-8.0f, -0.62f, -6.0f);
	poop_object->rotate(-90.0f, 0.0f, 0.0f);
	poop_object->scale(0.004);
	drawableObjects.push_back(poop_object);

	DrawableObject* house_object = new DrawableObject(camera, house_model, shaderProgram, material, house_texture);
	house_object->translate(-6.0f, -1.0f, -6.0f);
	house_object->scale(0.2);
	drawableObjects.push_back(house_object);

	for (int i = 0; i < 50; ++i) {
		DrawableObject* tree = new DrawableObject(camera, tree_model, shaderProgram, tree_material, tree_texture);
		RandomTransform(tree, i);
		drawableObjects.push_back(tree);

		DrawableObject* bush = new DrawableObject(camera, bush_model, shaderProgram2, bush_material, nullptr);
		RandomTransform2(bush, i);
		drawableObjects.push_back(bush);
	}

	Light* light1 = new Light(vec3(0.0f, 1.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
	light1->setType(SPOT);
	light1->setAngle(70.0f);
	light1->setIntensity(1);
	light1->setAttenuation(0.95f, 0.045f, 0.0072f);
	shaderProgram2->addLight(light1);
	shaderProgram->addLight(light1);

	Light* light2 = new Light(vec3(-6.0f, 2.0f, -3.6f), vec3(1.0f, 1.0f, 1.0f));
	light2->setType(SPOT);
	light2->setAngle(5.0f);
	light2->setIntensity(0.8);
	light2->setAttenuation(0.95f, 0.3f, 0.12f);
	shaderProgram2->addLight(light2);
	shaderProgram->addLight(light2);

	SpotLight* spotLight = new SpotLight(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
	spotLight->setAngle(10.0f);
	vec3 dir = vec3(0.0f, -1.0f, 0.0f);
	spotLight->setDirection(dir);
	shaderProgram->addLight(spotLight);
	shaderProgram2->addLight(spotLight);
}

void Scene::RandomTransform(DrawableObject* object, int i) {
	float x = static_cast<float>(rand() % 30 - 15) / 3.0f;
	float z = static_cast<float>(rand() % 30 - 15) / 3.0f;
	object->translate(x, -1.0f, z);

	float scale = 0.03f + static_cast<float>(rand() % 8) / 100.0f;
	object->scale(scale);
}
void Scene::RandomTransform2(DrawableObject* object, int i) {
	float x = static_cast<float>(rand() % 30 - 15) / 3.0f;
	float z = static_cast<float>(rand() % 30 - 15) / 3.0f;
	object->translate(x, -1.0f, z);

	float scale = 0.5f + static_cast<float>(rand() % 4) / 10.0f;
	object->scale(scale);
}
void Scene::CreateFourShaderLightsScene()
{
	ShaderProgram* shaderProgram1 = new ShaderProgram(camera);
	ShaderProgram* shaderProgram2 = new ShaderProgram(camera);
	ShaderProgram* shaderProgram3 = new ShaderProgram(camera);
	ShaderProgram* shaderProgram4 = new ShaderProgram(camera);

	shaderProgram1->initShader("Shaders/vertex.glsl", "Shaders/constant_fragment.glsl");
	shaderProgram2->initShader("Shaders/vertex.glsl", "Shaders/lambert_fragment.glsl");
	shaderProgram3->initShader("Shaders/vertex.glsl", "Shaders/blin_phong_fragment.glsl");
	shaderProgram4->initShader("Shaders/vertex.glsl", "Shaders/phong_fragment.glsl");

	Light* light1 = new Light(vec3(0.0f, 0.3f, 0.3f), vec3(0.385f, 0.647f, 0.812f));

	shaderProgram1->addLight(light1);
	shaderProgram2->addLight(light1);
	shaderProgram3->addLight(light1);
	shaderProgram4->addLight(light1);

	Material* bushMaterial = new Material(vec3(0.3f, 0.2f, 0.6f), vec3(0.4f, 0.7f, 0.4f), vec3(0.1f, 0.1f, 0.1f), 10.0f);
	Material* suziMaterial = new Material(vec3(0.3f, 0.3f, 0.3f), vec3(0.6f, 0.4f, 0.6f), vec3(0.3f, 0.32f, 0.3f), 20.0f);
	Material* sphereMaterial = new Material(vec3(0.6f, 0.0f, 0.5f), vec3(0.3f, 0.8f, 0.7f), vec3(0.5f, 0.5f, 0.5f), 30.0f);
	Material* giftMaterial = new Material(vec3(0.1f, 0.1f, 0.1f), vec3(0.1f, 0.5f, 0.1f), vec3(0.5f, 0.5f, 0.5f), 30.0f);

	vector<float> bushVertices(bushes, bushes + sizeof(bushes) / sizeof(bushes[0]));
	Model* bush_model = new Model(bushVertices, false);

	DrawableObject* bushObject = new DrawableObject(camera, bush_model, shaderProgram1, bushMaterial, nullptr);
	bushObject->translate(-0.7f, -0.1f, 0.0f);
	bushObject->scale(0.3f);
	drawableObjects.push_back(bushObject);

	vector<float> suziSmoothVertices(suziSmooth, suziSmooth + sizeof(suziSmooth) / sizeof(suziSmooth[0]));
	Model* suziModel = new Model(suziSmoothVertices, false);

	DrawableObject* suziObject = new DrawableObject(camera, suziModel, shaderProgram2, suziMaterial, nullptr);
	suziObject->translate(-0.13f, 0.0f, 0.0f);
	suziObject->scale(0.1f);
	drawableObjects.push_back(suziObject);

	vector<float> sphereVertices(sphere, sphere + sizeof(sphere) / sizeof(sphere[0]));
	Model* sphereModel = new Model(sphereVertices, false);

	DrawableObject* sphereObject = new DrawableObject(camera, sphereModel, shaderProgram3, sphereMaterial, nullptr);
	sphereObject->translate(-0.4f, 0.0f, 0.0f);
	sphereObject->scale(0.1f);
	drawableObjects.push_back(sphereObject);

	vector<float> giftVertices(gift, gift + sizeof(gift) / sizeof(gift[0]));
	Model* giftModel = new Model(giftVertices, false);

	DrawableObject* giftObject = new DrawableObject(camera, giftModel, shaderProgram4, giftMaterial, nullptr);
	giftObject->translate(0.15f, -0.1f, 0.0f);
	giftObject->scale(0.5f);
	drawableObjects.push_back(giftObject);
}

void Scene::DrawScene(float deltaTime) {

	if (this->skybox) {
		skybox->Draw(deltaTime);
	}

	// Zapisování ID do stencil bufferu
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);  // Povolit zápis

	for (auto drawableObject : drawableObjects) {

		if (drawableObject->getBezierCurve()) {
			drawableObject->Update(deltaTime);
		}
		glStencilFunc(GL_ALWAYS, drawableObject->getID(), 0xFF);
		drawableObject->Draw(deltaTime);
	}
	glStencilMask(0x00);
}

void Scene::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	controls->mouseCallback(window, xpos, ypos);
}

void Scene::processInput(GLFWwindow* window, float deltaTime) {
	if (controls) {
		controls->processInput(window, deltaTime);
	}
}

void Scene::SetSkybox(DrawableObject* model) {
	this->skybox = model;
}

void Scene::setSelectedObject(int index) {
	if (index >= 0 && index < drawableObjects.size()) {
		this->selectedObject = drawableObjects[index];
		printf("Vybrán objekt s indexem %d\n", index);
	}
}

void Scene::changeSkyBoxState() {
	if (this->skybox_model) {
		this->skybox_model->setStatic(!this->skybox_model->getIsStatic());
	}
}

void Scene::addDrawableObject(DrawableObject* drawableObject) {
	this->drawableObjects.push_back(drawableObject);
}

DrawableObject* Scene::getObjectByID(int id) {
	for (DrawableObject* object : drawableObjects) {
		if (object->getID() == id) {
			return object;
		}
	}
	return nullptr;
}

void Scene::removeDrawableObject(DrawableObject* object) {
	drawableObjects.erase(remove(drawableObjects.begin(), drawableObjects.end(), object), drawableObjects.end());
}