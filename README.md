# raw_renderer
--- _this project is based on ssloy's tinyrenderer: https://github.com/ssloy/tinyrenderer_ ---

My attempt at creating a maximally functional renderer from scratch, that is an extention of ssloy's tinyrender repo.
The main goal is project-based learning, but since I add some functionality that is not present in the original it might prove useful for future learners.

Below is the list of extentions in comparison to ssloy's code:

## extension log 

##### drawing wireframes

- Added the possibility of rescaling and centering imported .obj files. The original code assumes that the vertex coordinates go from -1 to 1, 
thus making it impossible to render larger obj's.

- Extended the class of .obj files available for import. The original code assumes the face elements in the format vertex_idx/texture_idx/normal_idx. 
However not every .obj file includes texture and/or normal indices. This has been fixed to recognized all formats.


*Huge thanks to ssloy for providing us, newbies with such valuable materials!*



