#ifndef CYCLUS_TESTS_RESOURCE_HELPERS_H_
#define CYCLUS_TESTS_RESOURCE_HELPERS_H_

#include "composition.h"
#include "material.h"
#include "generic_resource.h"
#include "test_context.h"
#include "mock_facility.h"
#include "request.h"
#include "bid.h"

namespace test_helpers {

/// @brief just some simple helper functions when dealing with resources and
/// exchanges
static int u235 = 92235;
static double helper_qty = 4.5;
    
static cyclus::Material::Ptr get_mat(int iso, double qty) {
  cyclus::CompMap cm;
  cm[iso] = qty;
  cyclus::Composition::Ptr comp = cyclus::Composition::CreateFromMass(cm);
  return cyclus::Material::CreateUntracked(qty, comp);
}

static cyclus::Material::Ptr get_mat() {
  return get_mat(u235, helper_qty);
}

static cyclus::TestContext helper_tc;
static MockFacility trader(helper_tc.get());

static cyclus::Request<cyclus::Material>::Ptr get_req(std::string commod = "") {
  return cyclus::Request<cyclus::Material>::Ptr(
      new cyclus::Request<cyclus::Material>(get_mat(), &trader, commod));
}

static cyclus::Bid<cyclus::Material>::Ptr get_bid() {
  return cyclus::Bid<cyclus::Material>::Ptr(
      new cyclus::Bid<cyclus::Material>(get_req(), get_mat(), &trader));
}

static double converter(cyclus::Material::Ptr r) {
  return r->quantity() * helper_qty;
}

} // namespace test_helpers

#endif // ifndef CYCLUS_TESTS_RESOURCE_HELPERS_H_
