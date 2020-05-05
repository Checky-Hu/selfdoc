#/bin/bash
subkey generate
# ${SECRET_PHRASE} phrase will be showed.
subkey --ed25519 inspect ${SECRET_PHRASE}
