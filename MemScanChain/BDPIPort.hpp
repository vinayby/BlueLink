/*
 * BDPIPort.hpp
 *
 *  Created on: Mar 29, 2016
 *      Author: jcassidy
 */

#ifndef MEMSCANCHAIN_BDPIPORT_HPP_
#define MEMSCANCHAIN_BDPIPORT_HPP_

#include <cinttypes>

class BDPIPort
{
public:
	/// Status words: Ready means you can read this tick, Wait means port not finished but can't provide/accept this cycle
	enum Status : uint8_t { Ready=0, Wait=1, End=255 };

	BDPIPort();
	virtual ~BDPIPort();

	////// Wrappers - do not override (use private virtual implementation funcs below)
	Status	status() 					const;
	void	readData(uint32_t* ret);
	void	writeData(const uint32_t* data);
	void 	close();

	////// Internal-use functions
	void		status(Status s);

private:
	virtual void implementClose()						{}
	virtual void implementReadData(uint32_t*)			{}
	virtual void implementWriteData(const uint32_t*)	{}
	Status			m_status=Wait;
};


extern "C"
{
	uint8_t 	bdpi_portGetStatus(uint64_t portPtr);								// 0=ready, 1=wait, 255=end
	void		bdpi_portGetReadData(uint32_t* ret,uint64_t portPtr);
	void		bdpi_portPutWriteData(uint64_t portPtr,uint32_t* data);
	void		bdpi_portClose(uint64_t);
}


#endif /* MEMSCANCHAIN_BDPIPORT_HPP_ */
