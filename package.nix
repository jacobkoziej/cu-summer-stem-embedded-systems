# SPDX-License-Identifier: MPL-2.0

{
  lib,
  mdbook,
  pkgs,
}:

let
  inherit (lib) fileset;

  book = lib.importTOML ./book.toml;

  inherit (book.build) build-dir;

in
pkgs.stdenvNoCC.mkDerivation {
  name = "book";

  src = fileset.toSource {
    root = ./.;
    fileset = fileset.gitTracked ./.;
  };

  nativeBuildInputs = [
    mdbook
  ];

  buildPhase = ''
    mdbook build
  '';

  installPhase = ''
    mkdir -p $out
    mv ${build-dir}/*  $out
    mv ${build-dir}/.* $out
  '';
}
