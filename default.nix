let nixpkgs = import <nixpkgs> {}; in
{
  dependencies = with nixpkgs; [ pkg-config clang-tools clang ccls glibc gtk4 cglm cairo ];
}
