#!/bin/bash
cd ${HOME}/Documents/block-chain/substrate/substrate
./target/release/node-template \
  --base-path /tmp/bob \
  --chain=local \
  --bob \
  --port 30334 \
  --ws-port 9945 \
  --rpc-port 9934 \
  --telemetry-url ws://telemetry.polkadot.io:1024 \
  --validator \
  --bootnodes /ip4/192.168.1.104/tcp/30333/p2p/
