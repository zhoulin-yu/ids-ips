{
  "targets": [
    {
      "target_name": "idsips",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [
        "./sources/blocage.c",
        "./sources/Comportement.c",
        "./sources/signature.c",
        "./sources/main.c",
	"./sources/index.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
