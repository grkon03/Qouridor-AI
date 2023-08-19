#pragma once

#include "bitboard.hpp"
#include "types.hpp"

#include "bitboardConst.hpp"

namespace QuoridorAI
{
    /**
     * @brief Wall by Bitboard expression
     */
    template <WallDir direction>
    class WallBBOD : public Bitboard96
    {
    public:
        // constructors

        WallBBOD();
        WallBBOD(const Bitboard96 &);
        WallBBOD(const WallBBOD &);

        // functions

        /**
         * @brief verify whether there is wall at one section of walls
         *
         * @param file lower file of square edges of the section
         * @param rank lower rank of square edges of the section
         *
         * @note should Bottom-Left Square edge
         * @note for speed, no verification that rank or file is out of range
         */
        bool IsThereWall(File file, Rank rank) const;

        /**
         * @brief verify whether there is wall at one section of walls
         *
         * @param se bottom-left one of square edges of the section
         *
         * @note should Bottom-Left Square edge
         * @note for speed, no verification that square edge
         */
        bool IsThereWall(SquareEdge se) const;
    };

    template <WallDir direction>
    WallBBOD<direction>::WallBBOD() {}
    template <WallDir direction>
    WallBBOD<direction>::WallBBOD(const Bitboard96 &bb) : Bitboard96(bb) {}
    template <WallDir direction>
    WallBBOD<direction>::WallBBOD(const WallBBOD &wb) : Bitboard96(wb) {}

    template <>
    /**
     * @brief verify whether there is wall at one section of walls
     *
     * @param file lower file of square edges of the section
     * @param rank rank of the section of walls
     *
     * @note should Bottom-Left Square edge
     * @note for speed, no verification that rank or file is out of range
     */
    inline bool WallBBOD<Horizontal>::IsThereWall(File file, Rank rank) const
    {
        return (operator&(Constant::oneBitMask96[(rank - 1) * 9 + file]) != 0);
    }

    template <>
    /**
     * @brief verify whether there is wall at one section of walls
     *
     * @param file file of the section of walls
     * @param rank lower rank of square edges of the section
     *
     * @note should Bottom-Left Square edge
     * @note for speed, no verification that rank or file is out of range
     */
    inline bool WallBBOD<Vertical>::IsThereWall(File file, Rank rank) const
    {
        return (operator&(Constant::oneBitMask96[rank * 8 + file - 1]) != 0);
    }

    template <WallDir direction>
    /**
     * @brief verify whether there is wall at one section of walls
     *
     * @param se bottom-left one of square edges of the section
     *
     * @note should Bottom-Left Square edge
     * @note for speed, no verification that square edge
     */
    inline bool WallBBOD<direction>::IsThereWall(SquareEdge se) const
    {
        return IsThereWall(GetRank(se), GetFile(se));
    }
}