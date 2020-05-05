#!/bin/bash
# Export current chain spec.
node-template build-spec --chain=local > customSpec.json
# Generate raw chain spec.
node-template build-spec --chain selfSpec.json --raw > selfSpecRaw.json
