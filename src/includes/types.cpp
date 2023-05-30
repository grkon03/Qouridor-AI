#include "types.hpp"

namespace QuoridorAI
{
    Square MakeSquare(SquareEdge se1, SquareEdge se2)
    {
        if (se1 == se2)
        {
            return Square::SquareInvalid;
        }
        else if (se1 > se2)
        {
            if (se1 - se2 == 11)
                return Square(se2 + se1 << 8);
            else if (se1 - se2 == 9)
                return Square((se2 - 1) + (se1 + 1) << 8);
            else
                return Square::SquareInvalid;
        }
        else
        {
            if (se2 - se1 == 1 || se2 - se1 == 10)
                return Square(se1 + se2 << 8);
            else
                return Square::SquareInvalid;
        }
    }

    Fence MakeFence(SquareEdge se1, SquareEdge se2)
    {
        if (se1 == se2)
        {
            return Fence::FenceInvalid;
        }
        else if (se1 > se2)
        {
            if (se1 - se2 == 2 || se1 - se2 == 20)
                return Fence(se2 + se1 << 8);
            else
                return Fence::FenceInvalid;
        }
        else
        {
            if (se2 - se1 == 2 || se2 - se1 == 20)
                return Fence(se1 + se2 << 8);
            else
                return Fence::FenceInvalid;
        }
    }

    Move MakeMove(SquareEdge se1, SquareEdge se2)
    {
        int p = se1 - se2;
        if (se1 == se2)
        {
            return Move::MoveInvalid;
        }
        else if (p > 0)
        {
            switch (p)
            {
            case 2:
            case 20:
            case 11:
                return Move(se2 + se1 << 8);
            case 9:
                return Move(se2 - 1 + (se1 + 1) << 8);
            default:
                return Move::MoveInvalid;
            }
        }
        else
        {
            switch (p)
            {
            case -2:
            case -20:
            case -11:
                return Move(se1 + se2 << 8);
            case -9:
                return Move(se1 - 1 + (se2 + 1) << 8);
            default:
                return Move::MoveInvalid;
            }
        }
    }

    bool IsKingMove(Move move)
    {
        int p = move >> 8 - move & 0xff;
        return (p == 11);
    }

    bool IsFenceMove(Move move)
    {
        int p = move >> 8 - move & 0xff;
        return (p == 2 || p == 20);
    }

    Move CastToMove(Square square)
    {
        return Move(square);
    }

    Move CastToMove(Fence fence)
    {
        return Move(fence);
    }

    Square CastToSquare(Move move)
    {
        if (IsKingMove(move))
            return Square(move);
        else
            return Square::SquareInvalid;
    }

    Fence CastToFence(Move move)
    {
        if (IsFenceMove(move))
            return Fence(move);
        else
            return Fence::FenceInvalid;
    }
}