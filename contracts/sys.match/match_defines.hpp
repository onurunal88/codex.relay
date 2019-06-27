#ifndef CODEX_INCLUED_SYS_MATCH_DEFINES_HPP_
#define CODEX_INCLUED_SYS_MATCH_DEFINES_HPP_
#pragma once

#include <string>
#include <vector>

#include <eosiolib/types.hpp>
#include <eosiolib/eosio.hpp>

namespace eosio {

   namespace __details {
      void splitMemo( std::vector<std::string>& results, const std::string& memo, char separator ) {
         auto start = memo.cbegin();
         auto end = memo.cend();

         for( auto it = start; it != end; ++it ) {
            if( *it == separator ) {
               results.emplace_back(start, it);
               start = it + 1;
            }
         }
         if (start != end) results.emplace_back(start, end);
      }
   }

   enum class trade_func_typ : uint64_t {
      match              = 1,
      bridge_addmortgage = 2,
      bridge_exchange    = 3,
      trade_type_count   = 4
   };

   struct sys_bridge_addmort {
      name         trade_name;
      account_name trade_maker = 0;
      uint64_t     type        = 0;

      inline void parse( const std::string& memo ) {
         std::vector<std::string> memoParts;
         memoParts.reserve( 8 );
         __details::splitMemo( memoParts, memo, ';' );

         eosio_assert( memoParts.size() == 3, "memo is not adapted with bridge_addmortgage" );

         this->trade_name.value = ::eosio::string_to_name( memoParts[0].c_str() );
         this->trade_maker = ::eosio::string_to_name( memoParts[1].c_str() );
         this->type = atoi( memoParts[2].c_str() );

         eosio_assert( this->type == 1 || this->type == 2,
                       "type is not adapted with bridge_addmortgage" );
      }
   };

   struct sys_bridge_exchange {
      name         trade_name;
      account_name trade_maker = 0;
      account_name recv        = 0;
      uint64_t     type;

      inline void parse( const std::string& memo ){
         std::vector<std::string> memoParts;
         memoParts.reserve( 8 );
         __details::splitMemo( memoParts, memo, ';' );

         eosio_assert( memoParts.size() == 4, "memo is not adapted with bridge_addmortgage" );

         this->trade_name.value = ::eosio::string_to_name( memoParts[0].c_str() );
         this->trade_maker = ::eosio::string_to_name( memoParts[1].c_str() );
         this->recv = ::eosio::string_to_name( memoParts[2].c_str() );
         this->type = atoi( memoParts[3].c_str() );

         eosio_assert( this->type == 1 || this->type == 2,
                       "type is not adapted with bridge_addmortgage" );
      }
   };
} // namespace codex

#endif // CODEX_INCLUED_SYS_MATCH_DEFINES_HPP_
