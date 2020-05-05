#!/bin/bash
cd ${HOME}/Documents/block-chain/substrate/substrate
./target/release/node-template \
  --base-path /tmp/key2 \
  --chain ../scripts/selfSpecRaw.json \
  --port 30334 \
  --ws-port 9945 \
  --rpc-port 9934 \
  --telemetry-url ws://telemetry.polkadot.io:1024 \
  --validator \
  --name Key2
