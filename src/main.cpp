#include "Command.h"
#include "Game.h"
#include "Response.h"
#include <string>

int main() {

  Command cmd;
  Game game;
  std::string resp;

  while (cmd.type != Command::T_QUIT) {
    cmd.readFromStdin();
    switch (cmd.type) {
      case Command::T_SET_GAME:
        if (game.setType(cmd.strArg)) {
          Response::success("");
        } else {
          Response::fail("Unknown game type [" + cmd.strArg + "].");
        }
        break;

      case Command::T_CLEAR_BOARD:
        game.restart();
        Response::success("");
        break;

      case Command::T_CPUTIME:
        resp = std::to_string(game.clock.getSeconds());
        Response::success(resp);
        break;

      case Command::T_GENMOVE:
        resp = game.findMove(cmd.intArg);
        // game.board.print();
        Response::success(resp);
        break;

      case Command::T_PLAY:
        game.makeMove(cmd.intArg, cmd.strArg);
        // game.board.print();
        Response::success("");
        break;

      case Command::T_UNKNOWN:
        Response::fail("Unknown command [" + cmd.strArg + "].");
        break;
    }
  }

  game.end();
  Response::success("");
  return 0;
}
