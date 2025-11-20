Para "instalar" essa biblioteca e deixá-la pronta para uso no seu projeto, você precisa rodar o comando de instalação do Conan.

**Importante:** O Conan não instala a biblioteca no seu sistema operacional (como o `apt` ou `pacman` fariam em `/usr/lib`). Ele instala em um **cache local** (geralmente na pasta `~/.conan2/`) e gera arquivos na sua pasta de projeto para que o seu compilador saiba onde encontrar a biblioteca.

Aqui está o passo a passo:

### 1\. O comando de instalação

Abra o terminal na mesma pasta onde está o seu `conanfile.py` e execute:

```bash
conan install . --build=missing
```

Se você quiser especificar que é para **Release** (produção/otimizado) ou **Debug**, use:

```bash
conan install . --build=missing -s build_type=Release
```

**O que esse comando faz:**

  * **`.`**: Lê o `conanfile.py` da pasta atual.
  * **`--build=missing`**: Se o Conan não encontrar um binário pré-compilado do `libx265` para o seu sistema específico (Linux/Windows, versão do compilador, arquitetura), ele vai baixar o código fonte e compilar automaticamente para você.
  * **Geração de arquivos:** Como seu arquivo tem `cmake_layout(self)`, ele vai criar uma pasta `build/` (ou `build/Release`) com os arquivos necessários para o CMake (`conan_toolchain.cmake` e `x265-config.cmake` ou similares).

-----

### 2\. Como usar no seu CMakeLists.txt

Como você definiu `generators = "CMakeDeps", "CMakeToolchain"`, o Conan preparou tudo para integração transparente.

No seu `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.15)
project(MeuProjeto)

# Procura pelo pacote instalado pelo Conan
find_package(libx265 REQUIRED)

add_executable(meu_app main.cpp)

# Linka a biblioteca ao seu executável
target_link_libraries(meu_app PRIVATE libx265::libx265)
```

-----

### 3\. Como compilar o projeto

Agora, ao rodar o CMake, você precisa avisar para ele usar o arquivo de "toolchain" que o Conan gerou.

**Se estiver no Linux/Mac:**

```bash
cd build/Release
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

**Se estiver usando CMake Presets (Recomendado para Conan 2.0+):**
O `cmake_layout` gera presets automaticamente. Você pode simplesmente rodar:

```bash
cmake --preset conan-release
cmake --build --preset conan-release
```

### Resumo

O comando mágico é `conan install . --build=missing`. Isso baixa a `libx265`, coloca no cache e prepara seu projeto para encontrá-la.

