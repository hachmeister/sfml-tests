#include <SFML/Graphics.hpp>

const std::string vertexShader = \
  "void main()" \
  "{" \
  "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;" \
  "  gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;" \
  "  gl_FrontColor = gl_Color;" \
  "}";

const std::string fragmentShader = \
  "uniform sampler2D texture;" \
  "void main()" \
  "{" \
  "  vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);" \
  "  gl_FragColor = gl_Color * pixel;" \
  "}";

void updateView(sf::View* view, int width, int height)
{
  view->setSize(width, height);
}

int main(int argc, char* argv[])
{
  sf::RenderWindow window(sf::VideoMode(1024, 768), "Texture Test", sf::Style::Close);
  window.setVerticalSyncEnabled(true);

  sf::Vector2u size = window.getSize();
  sf::View view;
  view.setCenter(size.x/2, size.y/2);
  updateView(&view, size.x, size.y);

  bool drawShader = false;

  sf::VertexArray vertices;
  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(4);
  sf::Vertex* quad = &vertices[0];

  quad[0].position = sf::Vector2f(256, 128);
  quad[1].position = sf::Vector2f(768, 128);
  quad[2].position = sf::Vector2f(768, 640);
  quad[3].position = sf::Vector2f(256, 640);

  quad[0].texCoords = sf::Vector2f(0, 0);
  quad[1].texCoords = sf::Vector2f(32.0, 0);
  quad[2].texCoords = sf::Vector2f(32.0, 32.0);
  quad[3].texCoords = sf::Vector2f(0, 32.0);

  /*quad[0].texCoords = sf::Vector2f(0, 0);
  quad[1].texCoords = sf::Vector2f(1.0/16.0, 0);
  quad[2].texCoords = sf::Vector2f(1.0/16.0, 1.0/16.0);
  quad[3].texCoords = sf::Vector2f(0, 1.0/16.0);*/

  sf::Texture texture;
  texture.loadFromFile("data/grid.png");

  sf::Shader shader;
  shader.loadFromMemory(vertexShader, fragmentShader);
  shader.setParameter("texture", texture);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
        case sf::Event::Closed:
        {
          window.close();
        }
        break;

        case sf::Event::Resized:
        {
          updateView(&view, event.size.width, event.size.height);
        }
        break;

        case sf::Event::KeyPressed:
        {
          if (event.key.code == sf::Keyboard::Escape)
          {
            window.close();
          }
          if (event.key.code == sf::Keyboard::S)
          {
            drawShader = !drawShader;
          }
        }
        break;

        default:
          break;
      }
    }

    window.clear();

    window.setView(view);

    sf::RenderStates states;

    if (drawShader)
    {
      states.shader = &shader;
      window.draw(vertices, states);
    }
    else
    {
      states.texture = &texture;
      window.draw(vertices, states);
    }

    window.display();
  }

  return 0;
}
