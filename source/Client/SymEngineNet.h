/*
 * This is a part of the BugTrap package.
 * Copyright (c) 2005-2009 IntelleSoft.
 * All rights reserved.
 *
 * Description: .NET symbolic engine.
 * Author: Maksim Pyatkovskiy.
 *
 * This source code is only intended as a supplement to the
 * BugTrap package reference and related electronic documentation
 * provided with the product. See these sources for detailed
 * information regarding the BugTrap package.
 */

#pragma once

#ifdef _MANAGED

#include "BugTrapNet.h"
#include <stdexcept>

#pragma managed

using namespace System;
using namespace System::Threading;
using namespace System::Diagnostics;
using namespace System::Text;
using namespace System::Collections;
using namespace System::Reflection;

namespace IntelleSoft
{
	namespace BugTrap
	{
		private ref class StackFrameEnumerator
		{
		public:
			StackFrameEnumerator(Thread^ thread);
			StackFrameEnumerator(Exception^ exception);
			void InitStackTrace(void);
			StackFrame^ GetFirstStackTraceEntry(void);
			StackFrame^ GetNextStackTraceEntry(void);
			property System::Exception^ Exception
			{
				System::Exception^ get(void);
			}

		private:
			initonly StackTrace^ stackTrace;
			initonly System::Exception^ exception;
			int frameIndex;
		};

		inline StackFrameEnumerator::StackFrameEnumerator(Thread^ thread)
		{
			throw std::runtime_error("StackFrameEnumerator with a Thread is now Obsolete");

			//// Get the process ID
			//int processId = Process::GetCurrentProcess()->Id;

			//// Get the thread ID
			//int threadId = thread->ManagedThreadId;

			//// Create a new stack trace for the specified thread ID
			//StackTrace^ stackTrace = gcnew StackTrace(processId, true);

			////array<StackFrame^>^ frames = stackTrace->GetFrames();
			////for each (StackFrame ^ frame in frames) {
			////	if (frame->GetILOffset() != StackFrame::OFFSET_UNKNOWN) {
			////		// Get the method name
			////		String^ methodName = frame->GetMethod()->Name;

			////		// Print the method name to the console
			////		Console::WriteLine("Method name: " + methodName);
			////	}
			////}
			//
			//this->stackTrace = gcnew StackTrace(thread, true);
			//this->frameIndex = int::MaxValue;
		}

		inline StackFrameEnumerator::StackFrameEnumerator(System::Exception^ exception)
		{
			this->stackTrace = gcnew StackTrace(exception, true);
			this->frameIndex = int::MaxValue;
			this->exception = exception;
		}

		inline void StackFrameEnumerator::InitStackTrace(void)
		{
			this->frameIndex = 0;
		}

		inline StackFrame^ StackFrameEnumerator::GetFirstStackTraceEntry(void)
		{
			this->InitStackTrace();
			return this->GetNextStackTraceEntry();
		}

		inline System::Exception^ StackFrameEnumerator::Exception::get(void)
		{
			return this->exception;
		}

		private ref class AssemblyEnumerator
		{
		public:
			AssemblyEnumerator(void);
			void InitAssemblies(void);
			Assembly^ GetFirstAssembly(void);
			Assembly^ GetNextAssembly(void);

		private:
			initonly array<Assembly^>^ assemblies;
			IEnumerator^ assemblyEnumerator;
		};

		inline void AssemblyEnumerator::InitAssemblies(void)
		{
			this->assemblyEnumerator->Reset();
		}

		inline Assembly^ AssemblyEnumerator::GetFirstAssembly(void)
		{
			this->InitAssemblies();
			return this->GetNextAssembly();
		}
	}
}

#pragma unmanaged

#endif // _MANAGED
