scene = Scene.new()

simpleShader = Shader.new("://Simple.shader")
simpleTextureShader = Shader.new("://SimpleTexture.shader")

texture = Texture.new("Textures/Test.jpg")

cubeMesh = Mesh.new("://Cube.obj")
teapotMesh = Mesh.new("Models/Teapot.obj")

blueMaterial = Material.new(simpleShader)
blueMaterial:set_vec3("Albedo", Vec3.new(0.0, 0.0, 1.0))
blueMaterial:set_float("Metallic", 0.7)
blueMaterial:set_vec3("Ambient", Vec3.new(0.0))
blueMaterial:set_float("Roughness", 0.7)

whiteMaterial = Material.new(simpleShader)
whiteMaterial:set_vec3("Albedo", Vec3.new(1.0, 1.0, 1.0))
whiteMaterial:set_float("Metallic", 0.7)
whiteMaterial:set_vec3("Ambient", Vec3.new(0.0))
whiteMaterial:set_float("Roughness", 0.7)

greenMaterial = Material.new(simpleShader)
greenMaterial:set_vec3("Albedo", Vec3.new(0.0, 1.0, 0.0))
greenMaterial:set_float("Metallic", 0.7)
greenMaterial:set_vec3("Ambient", Vec3.new(0.0))
greenMaterial:set_float("Roughness", 0.7)

textureMaterial = Material.new(simpleTextureShader)
textureMaterial:set_texture("AlbedoTexture", texture)
textureMaterial:set_vec3("Ambient", Vec3.new(0.0))
textureMaterial:set_float("Metallic", 0.7)
textureMaterial:set_float("Roughness", 0.7)

camera = scene:register()

scene:add_transform(camera, Vec3.new(0.0, 7.5, 0.0), Vec3.new(0.0), Vec3.new(1.0))
scene:add_camera(camera)

light = scene:register()
scene:add_transform(light, Vec3.new(0.0, 2.0, 8.0), Vec3.new(0.0), Vec3.new(1.0))
scene:add_point_light(light, Vec3.new(1.0), 500.0)

teapot = scene:register()
scene:add_transform(teapot, Vec3.new(5.0, 0.0, 0.0), Vec3.new(0.0), Vec3.new(1.0))
scene:add_mesh_renderer(teapot, teapotMesh, whiteMaterial)

greenCube = scene:register()
scene:add_transform(greenCube, Vec3.new(-6.8, 4.5, -7.6), Vec3.new(0.0), Vec3.new(1.0))
scene:add_mesh_renderer(greenCube, cubeMesh, greenMaterial)

blueCube = scene:register()
scene:add_transform(blueCube, Vec3.new(7.5, 3.0, -7.8), Vec3.new(0.0), Vec3.new(1.0))
scene:add_mesh_renderer(blueCube, cubeMesh, blueMaterial)

textureCube = scene:register()
scene:add_transform(textureCube, Vec3.new(-5.0, 0.0, 0.0), Vec3.new(0.0), Vec3.new(1.0))
scene:add_mesh_renderer(textureCube, cubeMesh, textureMaterial)

return scene

