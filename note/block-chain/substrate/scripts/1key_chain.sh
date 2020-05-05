#!/bin/bash
cd ${HOME}/Documents/block-chain/substrate/substrate
./target/release/node-template \
  --base-path /tmp/key1 \
  --chain ../scripts/selfSpecRaw.json \
  --port 30333 \
  --ws-port 9944 \
  --rpc-port 9933 \
  --telemetry-url ws://telemetry.polkadot.io:1024 \
  --validator \
  --name Key1
