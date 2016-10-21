/*
 * MMORPG Server
 * Copyright (C) 2013
 *
 */
#include "CircularBuffer.h"

/** Constructor
 */
CircularBuffer::CircularBuffer()
{
	m_buffer = m_bufferEnd = m_regionAPointer = m_regionBPointer = nullptr;
	m_regionASize = m_regionBSize = 0;
}

/** Destructor
 */
CircularBuffer::~CircularBuffer()
{
	free(m_buffer);
}

/** Read bytes from the buffer
 * @param destination pointer to destination where bytes will be written
 * @param bytes number of bytes to read
 * @return true if there was enough data, false otherwise
 */
bool CircularBuffer::Read(void * destination, size_t bytes)
{
	// copy as much out of region a
	uint8* ptr = (uint8*)destination;
	size_t read_count = 0;
	if ((m_regionASize + m_regionBSize) < bytes)
		return false;

	// If we have both region A and region B, always "finish" off region A first, as
	// this will contain the "oldest" data
	if (bytes > 0 && m_regionASize > 0)
	{
		read_count = std::min(bytes, m_regionASize);
		memcpy(ptr, m_regionAPointer, read_count);
		m_regionASize -= read_count;
		m_regionAPointer += read_count;
		ptr += read_count;
		bytes -= read_count;
	}

	// Data left over? read the data from buffer B
	if (bytes > 0)
	{
		memcpy(ptr, m_regionBPointer, bytes);
		m_regionBSize -= bytes;
		m_regionBPointer += bytes;
	}

	// Is buffer A empty?, move buffer B to buffer A, to increase future per formance
	if (m_regionASize == 0)
	{		
		if (m_regionBSize > 0 && m_regionBPointer != m_buffer)
			memmove(m_buffer, m_regionBPointer, m_regionBSize);

		m_regionAPointer = m_buffer;
		m_regionASize = m_regionBSize;
		m_regionBPointer = NULL;
		m_regionBSize = 0;
	}

	return true;
}

/** Write bytes to the buffer
 * @param data pointer to the data to be written
 * @param bytes number of bytes to be written
 * @return true if was successful, otherwise false
 */
bool CircularBuffer::Write(const void * data, size_t bytes)
{
	// If buffer B exists, write to it.
	if (m_regionBPointer != NULL)
	{
		if (GetBFreeSpace() < bytes)
			return false;

		memcpy(&m_regionBPointer[m_regionBSize], data, bytes);
		m_regionBSize += bytes;
		return true;
	}

	// Otherwise, write to buffer A, or initialize buffer B depending on which has more space.
	if (GetAFreeSpace() < GetSpaceBeforeA())
	{
		AllocateB();
		if (GetBFreeSpace() < bytes)
			return false;

		memcpy(&m_regionBPointer[m_regionBSize], data, bytes);
		m_regionBSize += bytes;
		return true;
	}
	else
	{
		if (GetAFreeSpace() < bytes)
			return false;

		memcpy(&m_regionAPointer[m_regionASize], data, bytes);
		m_regionASize += bytes;
		return true;
	}
}

/** Returns the number of available bytes left.
 */
size_t CircularBuffer::GetSpace()
{
	if( m_regionBPointer != NULL )
		return GetBFreeSpace();
	else
	{
		// would allocating buffer B get us more data?
		if( GetAFreeSpace() < GetSpaceBeforeA() )
		{
			AllocateB();
			return GetBFreeSpace();
		}

		// or not?
		return GetAFreeSpace();
	}
}

/** Removes len bytes from the front of the buffer
 * @param len the number of bytes to "cut"
 */
void CircularBuffer::Remove(size_t len)
{
	// remove from A first before we remove from b
	size_t remove_count = 0;

	// If we have both region A and region B, always "finish" off region A first, as
	// this will contain the "oldest" data
	if (len > 0 && m_regionASize > 0)
	{
		remove_count = std::min(len, m_regionASize);
		m_regionASize -= remove_count;
		m_regionAPointer += remove_count;
		len -= remove_count;
	}

	// Data left over? cut the data from buffer B
	if (len > 0 && m_regionBSize > 0)
	{
		remove_count = std::min(len, m_regionBSize);
		m_regionBSize -= remove_count;
		m_regionBPointer += remove_count;
		len -= remove_count;
	}

	// is buffer A empty? move buffer B to buffer A, to increase future performance
	if (m_regionASize == 0)
	{		
		if (m_regionBSize > 0 && m_regionBPointer != m_buffer)
			memmove(m_buffer, m_regionBPointer, m_regionBSize);

		m_regionAPointer = m_buffer;
		m_regionASize = m_regionBSize;
		m_regionBPointer = NULL;
		m_regionBSize = 0;
	}
}

/** Allocate the buffer with room for size bytes
 * @param size the number of bytes to allocate
 */
void CircularBuffer::Allocate(size_t size)
{
	m_buffer = (uint8*)malloc(size);
	m_bufferEnd = m_buffer + size;
	m_regionAPointer = m_buffer;		// reset A to the start
}

/** Increments the "writen" pointer forward len bytes
 * @param len number of bytes to step
 */
void CircularBuffer::IncrementWritten(size_t len)			// known as "commit"
{
	if( m_regionBPointer != nullptr )
		m_regionBSize += len;
	else
		m_regionASize += len;
}

/** Returns a pointer at the "beginning" of the buffer, where data can be pulled from
 */
void * CircularBuffer::GetBufferStart()
{
	if( m_regionASize > 0 )
		return m_regionAPointer;
	else
		return m_regionBPointer;
		
}
