// Copyright (c) 2016 The Bitcoin XT developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef BITCOIN_BLOCKSENDER_H
#define BITCOIN_BLOCKSENDER_H

class CChain;
class CBlockIndex;
class CInv;
class CNode;
class CBlock;
class XThinReRequest;

// Handles network 'getdata' requests for blocks.
class BlockSender {
    public:
        BlockSender();

        // Is this inv a block inv?
        bool isBlockType(int invType) const;

        // Are we able (and do we want to) send this block?
        bool canSend(const CChain& activeChain, const CBlockIndex& block,
            CBlockIndex *pindexBestHeader);

        void send(const CChain& activeChain, CNode& node,
            const CBlockIndex& blockIndex, const CInv& inv);

        void sendBlock(CNode& node,
            const CBlockIndex& blockIndex, int invType);

        // Creates a response for a re-request for transactions missing
        // from a thin block.
        void sendReReqReponse(CNode& node, const CBlockIndex& blockIndex,
            const XThinReRequest& req);


    protected: // used in unit tests
        void triggerNextRequest(const CChain& activeChain, const CInv& inv, CNode& node);
        virtual bool readBlockFromDisk(CBlock& block, const CBlockIndex* pindex);
};

#endif
