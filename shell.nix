let
  nixpkgs = import <nixpkgs> {};
  settings = import ./default.nix;
in with nixpkgs; {
  umlapp = stdenv.mkDerivation {
    name = "umlapp";
    buildInputs = settings.dependencies;
  };
}
