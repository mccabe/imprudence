# -*- cmake -*-
#
# Download viewer artwork and skins even when using standalone

include(Variables)
include(Prebuilt)

if (NOT STANDALONE)
  use_prebuilt_binary(artwork)
  use_prebuilt_binary(skins-dark)
  use_prebuilt_binary(skins-gemini)
  use_prebuilt_binary(skins-meerkat)
else (NOT STANDALONE)
  set(STANDALONE OFF)
    use_prebuilt_binary(artwork)
    use_prebuilt_binary(skins-dark)
	use_prebuilt_binary(skins-gemini)
	use_prebuilt_binary(skins-meerkat)
  set(STANDALONE ON)
endif (NOT STANDALONE)
