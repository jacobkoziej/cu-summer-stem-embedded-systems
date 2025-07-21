# SPDX-License-Identifier: MPL-2.0

{
  description = "The Cooper Union - Summer STEM Embedded Systems: C-ing Beyond Arduino";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };

  outputs =
    inputs:

    inputs.flake-utils.lib.eachDefaultSystem (
      system:

      let
        pkgs = import inputs.nixpkgs {
          inherit system;
        };

        inherit (pkgs) lib;
        inherit (pkgs) python3;

        python3-pkgs = python3.withPackages (
          ps: with ps; [
            mdformat-footnote
            mdformat-simple-breaks
          ]
        );

      in
      {
        devShells.default = pkgs.mkShellNoCC (
          let
            avr-pkgs = pkgs.pkgsCross.avr;

            pre-commit-bin = "${lib.getBin pkgs.pre-commit}/bin/pre-commit";

          in
          {
            packages =
              (with pkgs; [
                arduino-cli
                commitlint-rs
                gnumake
                mdbook
                mdformat
                pre-commit
                python3-pkgs
                shfmt
                statix
                toml-sort
                treefmt
                yamlfmt
                yamllint
              ])
              ++ (with avr-pkgs.buildPackages; [
                binutils
                gcc
              ]);

            shellHook = ''
              ${pre-commit-bin} install --allow-missing-config > /dev/null
            '';
          }
        );

        formatter = pkgs.nixfmt-rfc-style;

        packages = rec {
          book = pkgs.callPackage ./package.nix { };

          default = book;
        };
      }
    );
}
