scene = Scene.new()

quadMesh = Mesh.new("://Quad.obj")
mandelbrotShader = Shader.new("Shaders/Mandelbrot.shader")
mandelbrotMaterial = Material.new(mandelbrotShader)
mandelbrotMaterial:set_int("MaxIterations", 1000)
mandelbrotMaterial:set_vec2("Position", Vec2.new(0.5, 0.0))
mandelbrotMaterial:set_float("Scale", 0.2)
mandelbrotMaterial:set_int("Julia", 0)
mandelbrotMaterial:set_float("JuliaC", 0.5)

mandelbrot = scene:register()
scene:add_transform(mandelbrot, Vec3.new(0.0, 1.0, 0.0), Vec3.new(0.0, 0.0, 0.0), Vec3.new(1.0))
scene:add_mesh_renderer(mandelbrot, quadMesh, mandelbrotMaterial)

camera = scene:register();
scene:add_transform(camera, Vec3.new(0.0, 1.0, 0.5), Vec3.new(0.0, 0.0, 0.0), Vec3.new(1.0))
scene:add_camera(camera, 80.0, 0.1, 100.0)

return scene