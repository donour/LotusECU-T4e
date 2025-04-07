import can

ARB_ID_32BIT = 0x50
ARB_ID_16BIT = 0x51
ARB_ID_8BIT = 0x52

steering_msg = can.Message(arbitration_id=ARB_ID_16BIT, data = [0x40, 0x00, 0x27, 0x44], is_extended_id=False)
load_mesg = can.Message(arbitration_id=ARB_ID_8BIT, data = [0x40, 0x00, 0x1d, 0x44], is_extended_id=False)
rpm_mesg = can.Message(arbitration_id=ARB_ID_16BIT, data = [0x40, 0x00, 0x18, 0xd2], is_extended_id=False)

class MinimalCANLogger:
    """
    A minimal synchronous Python class for CAN messaging using python-can.
    """
    
    def __init__(self, channel='can0', interface='socketcan'):
        """
        Initialize the CAN connection.
        
        Args:
            channel (str): CAN channel name (default: 'can0')
            interface (str): CAN interface type (default: 'socketcan')
        """
        self.bus = can.Bus(
            channel=channel, 
            interface=interface,
			can_filters = [{
				"extended": False,
				"can_id": 0x7A0,
				"can_mask": 0x7FF
			}],
			bitrate = bitrate
        )
    
    def close(self):
        """Close the CAN interface."""
        if self.bus:
            self.bus.shutdown()
            self.bus = None
    
    def send_and_receive(self, msg):
        self.bus.send(msg)
        return self.bus.recv()
    
    def __enter__(self):
        """Context manager entry."""
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        """Context manager exit."""
        self.close()


# Example usage
if __name__ == "__main__":
    with MinimalCANLogger(channel='can0', interface='socketcan') as logger:
        response = logger.send_and_receive(steering_msg)