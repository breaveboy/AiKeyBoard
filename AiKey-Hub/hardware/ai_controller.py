from __future__ import annotations

import logging
from typing import Callable

from .packet_codec import McuPacketCodec
from .protocol_constants import AiAction, AiParameter, Command

logger = logging.getLogger(__name__)


AI_ACTION_NAMES = {
    AiAction.WAKE: "wake",
    AiAction.RUN: "run",
    AiAction.REPLACE: "replace",
}


class McuAiController:
    def __init__(self):
        self._event_handlers: list[Callable[[str], None]] = []

    def add_event_handler(self, handler: Callable[[str], None]) -> None:
        self._event_handlers.append(handler)

    def handle_packet(self, data: bytes) -> bool:
        packet = McuPacketCodec.decode(data)
        if packet is None:
            return False
        if packet["command"] != Command.AI_ACTION or packet["parameter"] != AiParameter.ACTION:
            return False

        payload = packet["payload"]
        if len(payload) < 1:
            logger.warning("AI action packet payload is too short: %s", payload.hex(" "))
            return True

        action_code = payload[0]
        try:
            action = AI_ACTION_NAMES[AiAction(action_code)]
        except ValueError:
            logger.warning("Unknown AI action code from MCU: 0x%02X", action_code)
            return True

        logger.info("AI action received from MCU: %s", action)
        for handler in self._event_handlers:
            handler(action)
        return True

    def encode_action(self, action: AiAction) -> bytes:
        return McuPacketCodec.encode(
            command=Command.AI_ACTION,
            parameter=AiParameter.ACTION,
            payload=bytes([action, 0x00]),
        )
